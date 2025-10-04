# PowerShell Script - Reorganize Documentation
# E:\UE_red_alert_2_v001\docs\UE_RTS_Course\reorganize_docs.ps1

Write-Host "Reorganizing documentation structure..." -ForegroundColor Cyan

$baseDir = $PSScriptRoot

# Create folders
$folders = @(
    "01_Planning",
    "02_AI_Pipeline", 
    "03_Maps_Environment",
    "04_UI_Design",
    "05_Week_Plans",
    "06_Assets_Lists",
    "07_Utilities"
)

Write-Host "Creating folder structure..." -ForegroundColor Yellow

foreach ($folder in $folders) {
    $path = Join-Path $baseDir $folder
    if (-not (Test-Path $path)) {
        New-Item -ItemType Directory -Path $path -Force | Out-Null
        Write-Host "  Created: $folder" -ForegroundColor Green
    } else {
        Write-Host "  Exists: $folder" -ForegroundColor Gray
    }
}

Write-Host "Moving files..." -ForegroundColor Yellow

# 01_Planning
$planningFiles = @(
    "README.md",
    "TECH_SPEC.md",
    "ROADMAP.md",
    "PROGRESS.md",
    "PROJECT_STATUS.md",
    "RU_EN_GLOSSARY.md"
)

foreach ($file in $planningFiles) {
    $source = Join-Path $baseDir $file
    $dest = Join-Path $baseDir "01_Planning\$file"
    if (Test-Path $source) {
        Move-Item -Path $source -Destination $dest -Force
        Write-Host "  Moved: $file to 01_Planning" -ForegroundColor Green
    }
}

# 02_AI_Pipeline
$aiFiles = @(
    "AI_ASSET_PIPELINE_RA2.md",
    "COMFYUI_WORKFLOW_RA2.md"
)

foreach ($file in $aiFiles) {
    $source = Join-Path $baseDir $file
    $dest = Join-Path $baseDir "02_AI_Pipeline\$file"
    if (Test-Path $source) {
        Move-Item -Path $source -Destination $dest -Force
        Write-Host "  Moved: $file to 02_AI_Pipeline" -ForegroundColor Green
    }
}

# 03_Maps_Environment
$mapsFiles = @(
    "RA2_MAP_CONVERSION_GUIDE.md",
    "MAPS_ENVIRONMENT_PLAN.md"
)

foreach ($file in $mapsFiles) {
    $source = Join-Path $baseDir $file
    $dest = Join-Path $baseDir "03_Maps_Environment\$file"
    if (Test-Path $source) {
        Move-Item -Path $source -Destination $dest -Force
        Write-Host "  Moved: $file to 03_Maps_Environment" -ForegroundColor Green
    }
}

# 04_UI_Design
$uiFiles = @(
    "RA2_MENU_UI_DESIGN.md"
)

foreach ($file in $uiFiles) {
    $source = Join-Path $baseDir $file
    $dest = Join-Path $baseDir "04_UI_Design\$file"
    if (Test-Path $source) {
        Move-Item -Path $source -Destination $dest -Force
        Write-Host "  Moved: $file to 04_UI_Design" -ForegroundColor Green
    }
}

# 05_Week_Plans
$weekFiles = @(
    "WEEK_2_5_ACTION_PLAN.md",
    "WEEK3_BUILDINGS_PIPELINE.md"
)

foreach ($file in $weekFiles) {
    $source = Join-Path $baseDir $file
    $dest = Join-Path $baseDir "05_Week_Plans\$file"
    if (Test-Path $source) {
        Move-Item -Path $source -Destination $dest -Force
        Write-Host "  Moved: $file to 05_Week_Plans" -ForegroundColor Green
    }
}

# 06_Assets_Lists
$assetsFiles = @(
    "RA2_UNITS_BUILDINGS_LIST.md"
)

foreach ($file in $assetsFiles) {
    $source = Join-Path $baseDir $file
    $dest = Join-Path $baseDir "06_Assets_Lists\$file"
    if (Test-Path $source) {
        Move-Item -Path $source -Destination $dest -Force
        Write-Host "  Moved: $file to 06_Assets_Lists" -ForegroundColor Green
    }
}

# 07_Utilities
$utilFiles = @(
    "LOCALIZATION.md"
)

foreach ($file in $utilFiles) {
    $source = Join-Path $baseDir $file
    $dest = Join-Path $baseDir "07_Utilities\$file"
    if (Test-Path $source) {
        Move-Item -Path $source -Destination $dest -Force
        Write-Host "  Moved: $file to 07_Utilities" -ForegroundColor Green
    }
}

# Special handling for пример диаграмы.txt
$diagramSource = Join-Path $baseDir "пример диаграмы.txt"
if (Test-Path $diagramSource) {
    $diagramDest = Join-Path $baseDir "07_Utilities\пример диаграмы.txt"
    Move-Item -Path $diagramSource -Destination $diagramDest -Force
    Write-Host "  Moved: diagram example to 07_Utilities" -ForegroundColor Green
}

# Move scripts folder
$scriptsSource = Join-Path $baseDir "scripts"
if (Test-Path $scriptsSource) {
    $scriptsDest = Join-Path $baseDir "07_Utilities\scripts"
    Move-Item -Path $scriptsSource -Destination $scriptsDest -Force
    Write-Host "  Moved: scripts folder to 07_Utilities" -ForegroundColor Green
}

# UE_KB stays as is

Write-Host ""
Write-Host "Reorganization complete!" -ForegroundColor Green
Write-Host ""
Write-Host "New structure created with 7 organized folders" -ForegroundColor Cyan
Write-Host "UE_KB folder unchanged" -ForegroundColor Cyan
Write-Host ""
Write-Host "Check git status to see moved files" -ForegroundColor Yellow
Write-Host "MASTER_INDEX.md already updated with new paths" -ForegroundColor Yellow
Write-Host ""
Write-Host "All done!" -ForegroundColor Green
