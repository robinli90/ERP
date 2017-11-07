param (
[string]$OutputDir,
[string]$BaseDir,
[string]$TargetFileName,
[string]$ConfuserConfigurationFile
)

function replace-file-content([string] $path, [string] $replace, [string] $replaceWith)
{
(Get-Content $path) |
Foreach-Object {$_ -replace $replace,$replaceWith}|
Out-File $path
}

# Let's first copy the configuration file to a temporary directory
echo "Obfuscating..."
$tempFile = [string]::Concat($BaseDir, "confuser.temp.crproj")
echo "Copying " $ConfuserConfigurationFile " to " $tempFile
Copy-Item $ConfuserConfigurationFile -Destination $tempFile
echo "Replacing placeholders..."
replace-file-content $tempFile "{OutputDir}" "$OutputDir"
replace-file-content $tempFile "{BaseDir}" "$BaseDir"
replace-file-content $tempFile "{TargetFileName}" "$TargetFileName"
echo "Performing Obfuscation..."
#start-process -wait "F:ToolsObfuscatorsConfuserEx_binConfuser.CLI.exe" "$tempFile"
echo "Obfuscation complete."
echo "Removing " $tempFile
Remove-Item $tempFile
echo "Done!!!"

echo "Done x2"

param (
[string]$OutputDir,
[string]$BaseDir,
[string]$TargetFileName,
[string]$ConfuserConfigurationFile
)

function replace-file-content([string] $path, [string] $replace, [string] $replaceWith)
{
(Get-Content $path) |
Foreach-Object {$_ -replace $replace,$replaceWith}|
Out-File $path
}

# Let's first copy the configuration file to a temporary directory
echo "Obfuscating..."
$tempFile = [string]::Concat($BaseDir, "confuser.temp.crproj")
echo "Copying " $ConfuserConfigurationFile " to " $tempFile
Copy-Item $ConfuserConfigurationFile -Destination $tempFile
echo "Replacing placeholders..."
replace-file-content $tempFile "{OutputDir}" "$OutputDir"
replace-file-content $tempFile "{BaseDir}" "$BaseDir"
replace-file-content $tempFile "{TargetFileName}" "$TargetFileName"
echo "Performing Obfuscation..."
#start-process -wait "F:ToolsObfuscatorsConfuserEx_binConfuser.CLI.exe" "$tempFile"
echo "Obfuscation complete."
echo "Removing " $tempFile
Remove-Item $tempFile
echo "Done!!!"

echo "Done x2
"param (
[string]$OutputDir,
[string]$BaseDir,
[string]$TargetFileName,
[string]$ConfuserConfigurationFile
)

function replace-file-content([string] $path, [string] $replace, [string] $replaceWith)
{
(Get-Content $path) |
Foreach-Object {$_ -replace $replace,$replaceWith}|
Out-File $path
}

# Let's first copy the configuration file to a temporary directory
echo "Obfuscating..."
$tempFile = [string]::Concat($BaseDir, "confuser.temp.crproj")
echo "Copying " $ConfuserConfigurationFile " to " $tempFile
Copy-Item $ConfuserConfigurationFile -Destination $tempFile
echo "Replacing placeholders..."
replace-file-content $tempFile "{OutputDir}" "$OutputDir"
replace-file-content $tempFile "{BaseDir}" "$BaseDir"
replace-file-content $tempFile "{TargetFileName}" "$TargetFileName"
echo "Performing Obfuscation..."
#start-process -wait "F:ToolsObfuscatorsConfuserEx_binConfuser.CLI.exe" "$tempFile"
echo "Obfuscation complete."
echo "Removing " $tempFile
Remove-Item $tempFile
echo "Done!!!"

echo "Done x2
"
