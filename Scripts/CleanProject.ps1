# Load the required .NET assembly for Windows Forms
Add-Type -AssemblyName "System.Windows.Forms"

# Get the path to the current user's Documents folder
$documentsPath = [Environment]::GetFolderPath("MyDocuments")

# Define the output directory and file path for BuildConfiguration.xml
$outputDir = "$documentsPath\Unreal Engine\UnrealBuildTool"
$outputFile = "$outputDir\BuildConfiguration.xml"

# Create the directory if it doesn't exist
if (-not (Test-Path -Path $outputDir)) {
    New-Item -Path $outputDir -ItemType Directory
}

# Define the XML content
$xmlContent = @"
<?xml version="1.0" encoding="utf-8"?>
<Configuration xmlns="https://www.unrealengine.com/BuildConfiguration">
    <VCProjectFileGenerator>
        <bIncludeEnginePrograms>false</bIncludeEnginePrograms>
        <bIncludeDotNetPrograms>false</bIncludeDotNetPrograms>
        <bIncludeTemplateFiles>false</bIncludeTemplateFiles>
    </VCProjectFileGenerator>
</Configuration>
"@

# Write the XML content to the file
Set-Content -Path $outputFile -Value $xmlContent -Force

# Confirm success
Write-Host "File created at $outputFile"

$baseDir = Split-Path -Path $PSScriptRoot -Parent

# Directories to remove
$dirsToRemove = @(
    "Saved",
    "Binaries",
    "Intermediate",
    "DerivedDataCache",
    "obj",
    "bin",
    ".vs",
    ".idea"
)

# Loop through the directories and remove them
foreach ($dir in $dirsToRemove) {
    $path = Join-Path -Path $baseDir -ChildPath $dir

    if ($dir -eq "Saved") {
        # Create a graphical Yes/No prompt asking the user if they want to clean the Saved folder
        $dialogResultSaved = [System.Windows.Forms.MessageBox]::Show(
            "Do you want to remove your editor and project settings?",  # Message text
            "Clean Settings",                           # Title text
            [System.Windows.Forms.MessageBoxButtons]::YesNo,  # Buttons: Yes and No
            [System.Windows.Forms.MessageBoxIcon]::Question    # Icon: Question mark
        )

        if ($dialogResultSaved -eq [System.Windows.Forms.DialogResult]::Yes) {
            Write-Host "Removing entire Saved folder..."
            Remove-Item -Path $path -Recurse -Force
        } else {
            Write-Host "Cleaning Saved folder but retaining Config/WindowsEditor..."

            # Remove everything inside Saved except Config/WindowsEditor
            $savedSubDirs = Get-ChildItem -Path $path -Directory -Force
            foreach ($subDir in $savedSubDirs) {
                $subDirPath = $subDir.FullName

                # Skip Config/WindowsEditor
                if ($subDir.Name -eq "Config") {
                    $windowsEditorPath = Join-Path -Path $subDirPath -ChildPath "WindowsEditor"
                    Get-ChildItem -Path $subDirPath -Force |
                        Where-Object { $_.FullName -ne $windowsEditorPath } |
                        Remove-Item -Recurse -Force
                    Write-Host "Retained Config/WindowsEditor but cleaned other subfolders in Config."
                    continue
                }

                Write-Host "Removing subdirectory: $subDirPath"
                Remove-Item -Path $subDirPath -Recurse -Force
            }

            # Remove files in Saved root
            Get-ChildItem -Path $path -File -Force | Remove-Item -Force
            Write-Host "Cleaned up files in Saved but retained Config/WindowsEditor."
        }
    }
    elseif (Test-Path -Path $path) {
        Write-Host "Removing directory: $path"
        Remove-Item -Path $path -Recurse -Force
    }
    else {
        Write-Host "Directory not found: $path"
    }
}


# Delete the solution file if it exists
$solutionFile = Join-Path -Path $baseDir -ChildPath "AircraftPrototype1.sln"
if (Test-Path -Path $solutionFile) {
    Write-Host "Deleting solution file: $solutionFile"
    Remove-Item -Path $solutionFile -Force
} else {
    Write-Host "Solution file not found: $solutionFile"
}

# Pause at the end to keep the window open
# Write-Host "Press any key to exit..."
# $null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
