#!/usr/bin/env groovy

/*
 * This Jenkinsfile is intended to run on Sensics' build servers and may fail anywhere else.
 * It makes assumptions about plugins being installed, labels mapping to nodes that can build what is needed, etc.
 *
 * The required labels are "java" and "docker" - "java" would be any node that can run Java builds. It doesn't need
 * to have Java installed, but some setups may have nodes that shouldn't have heavier builds running on them, so we
 * make this explicit. "docker" would be any node with docker installed.
 */

// TEST FLAG - to make it easier to turn on/off unit tests for speeding up access to later stuff.
def runTests = true
def failFast = false

// FIXME should things be in one list or a nested list?
properties(
    [
        pipelineTriggers([[$class: "GitHubPushTrigger"]]),
        buildDiscarder(logRotator(numToKeepStr: '10', artifactNumToKeepStr: '10')),
        [
            //$class: 'jenkins.model.BuildDiscarderProperty', strategy: [$class: 'LogRotator', numToKeepStr: '10', artifactNumToKeepStr: '10'],
            $class: 'CopyArtifactPermissionProperty', projectNames: '*'
        ],
    ]
)



def buildTypes = ['linux && gcc', 'linux && clang', 'vs2015', 'vs2017']
def configs = ['Debug', 'RelWithDebInfo']

def builds = [:]
for(i = 0; i < buildTypes.size(); i++) {
    def buildType = buildTypes[i]
    builds[buildType] = {
        node(buildType.toLowerCase()) {
            timestamps {
                // First stage is actually checking out the source. Since we're using Multibranch
                // currently, we can use "checkout scm".
                stage('Checkout') {
                    checkout scm
                }

                // Now run the actual build.
                stage("${buildType} Build / Test") {
                    timeout(time: 180, unit: 'MINUTES') {
                        git rev-parse HEAD > gitrev.txt
                        removeDirectory build
                        removeDirectory install
                        makeDirectory build
                        makeDirectory install
                        dir ('build') {
                            if (isUnix()) {
                                sh 'cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_INSTALL_PREFIX=${WORKSPACE}/install'
                                sh 'make -j4 install'
                                //sh ctest --extra-verbose
                                sh 'bin/LoadTest --gtest_output=xml'
                            } else {
                                def GENERATOR = ""
                                for (j = 0; j < configs.size(); j++) {
                                    def CONFIG = configs[i]
                                    bat 'cmake .. -G "${GENERATOR}" -DCMAKE_INSTALL_PREFIX="${WORKSPACE}/install"'
                                    bat 'cmake --build . --config "${CONFIG}" --target install'
                                    //bat ctest --build-config ${CONFIG} --extra-verbose
                                    bat 'bin\\Debug\\LoadTest.exe --gtest_output=xml:test_details.Debug.xml'
                                    bat 'bin\\RelWithDebInfo\\LoadTest.exe --gtest_output=xml:test_details.RelWithDebInfo.xml'
                                }
                            }
                        }
                    }
                }

                // Once we've built, archive the artifacts and the test results.
                stage("${buildType} Archive Artifacts / Test Results") {
                    if (isUnix()) {
                        sh 'git describe --tags > libfunctionality-ver.txt'
                        sh 'copy libfunctionality-ver.txt install'
                        sh '7za a libfunctionality-binary.7z install/*'
                    } else {
                        bat 'git describe --tags > libfunctionality-ver.txt'
                        bat 'copy libfunctionality-ver.txt install'
                        bat '7za a libfunctionality-binary.7z install\\*'
                    }


                    def files = findFiles(glob: '**/install/*')
                    renameFiles(files, buildType.toLowerCase())

                    archiveArtifacts artifacts: '**/install/*', fingerprint: true
                    if (runTests) {
                        junit healthScaleFactor: 1.0, testResults: '**/build/test_detail.xml'
                    }
                }
            }
        }
    }
}

builds.failFast = failFast
parallel builds

//
// Helper functions
//
void renameFiles(def files, String prefix) {
    for (i = 0; i < files.length; i++) {
        def newPath = files[i].path.replace(files[i].name, "${prefix}-${files[i].name}")
        def rename = "${files[i].path} ${newPath}"
        if (isUnix()) {
            sh "mv ${rename}"
        } else {
            bat "move ${rename}"
        }
    }
}

def removeFile(path) {
    echo "Deleting ${path}..."
    if (isUnix()) {
        sh "rm -f ${path}"
    } else {
        if (fileExists(path)) {
            bat "del /s /f /q ${path}"
        }
    }
}

def removeDirectory(path) {
    echo "Deleting ${path}..."
    if (isUnix()) {
        sh "rm -fr ${path}"
    } else {
        if (fileExists(path)) {
            bat "rmdir /s /q ${path}"
        }
    }
}

def makeDirectory(path) {
    echo "Creating ${path}..."
    if (isUnix()) {
        sh "mkdir -p ${path}"
    } else {
        if (!fileExists(path)) {
            bat "mkdir ${path}"
        }
    }
}

def copyArtifact(project, targetDirectory, flatten=false) {
    step([$class: 'CopyArtifact',
        projectName: "${project}",
        target: "${targetDirectory}",
        fingerprintArtifacts: true,
        flatten: flatten
    ]);
}

def moveTree(source, destination) {
    echo "Moving tree from ${source} to ${destination}..."
    bat "(robocopy /move /e \"${source}\" \"${destination}\") ^& if %ERRORLEVEL% LEQ 1 exit 0"
}

def powershell(command) {
    bat "powershell.exe -NonInteractive -ExecutionPolicy Bypass -Command \"\$ErrorActionPreference='Stop';[Console]::OutputEncoding=[System.Text.Encoding]::UTF8;${command};EXIT \$global:LastExitCode\""
}

//def windowsRenamePath(pattern, newpath) {
//    powershell "Get-ChildItem -Filter \"${pattern}\" | foreach { Rename-Item -NewName { \$_.Name -replace '-build-with-.*','' } -WhatIf }"
//}

def windowsRenamePath(pattern, destination) {
    echo "Renaming directory matching pattern ${pattern} to ${destination}..."
    //bat "for /D %%d in (${pattern}) do ((robocopy /move /e \"%%d\" \"${destination}\") ^& if %ERRORLEVEL% LEQ 1 exit 0)"
    bat "for /D %%d in (*) do (echo %%d)"
    bat "for /D %%d in (\"*\") do (echo %%d)"
    bat "for /D %%d in (\"${pattern}\") do (echo %%d)"
    bat "for /D %%d in (\"${pattern}\") do (rename %%d \"${destination}\")"
}



