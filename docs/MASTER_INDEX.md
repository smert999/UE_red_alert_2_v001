# 📚 MASTER INDEX - Полный указатель документации

**Проект:** Red Alert 2 Clone + Expansion (UE5)
**Обновлено:** 2025-10-04
**Путь:** `E:\UE_red_alert_2_v001\docs\`

---

## 🎯 QUICK START

**Новичок в проекте? Начни здесь:**
1. [README.md](UE_RTS_Course/01_Planning/README.md) - Overview проекта
2. [TECH_SPEC.md](UE_RTS_Course/01_Planning/TECH_SPEC.md) - Техническое задание
3. [ROADMAP.md](UE_RTS_Course/01_Planning/ROADMAP.md) - План разработки (12 недель)
4. [PROJECT_STATUS.md](UE_RTS_Course/01_Planning/PROJECT_STATUS.md) - Текущее состояние

**Хочешь начать работать? Смотри:**
- [WEEK_2_5_ACTION_PLAN.md](UE_RTS_Course/05_Week_Plans/WEEK_2_5_ACTION_PLAN.md) - Детальный план текущей недели

**⚠️ ВАЖНО: Для применения новой структуры:**
```powershell
cd E:\UE_red_alert_2_v001\docs\UE_RTS_Course
.\reorganize_docs.ps1
```

---

## 📁 НОВАЯ СТРУКТУРА ДОКУМЕНТАЦИИ

**⚠️ Структура реорганизована 2025-10-04!**
**Для применения запусти:** `docs/UE_RTS_Course/reorganize_docs.ps1`

```
docs/
├── MASTER_INDEX.md                      ← ВЫ ЗДЕСЬ
├── SUMMARY.md                           (Устарел - оставлен для истории)
├── BLUEPRINT_PR_DESCRIPTION.md          (Устарел - оставлен для истории)
│
└── UE_RTS_Course/
    ├── 01_Planning/                     📋 PLANNING & TRACKING
    │   ├── README.md                    - Overview, быстрые ссылки
    │   ├── TECH_SPEC.md                 - ТЗ (scope, constraints, tools) ✅
    │   ├── ROADMAP.md                   - 12-недельный план ✅
    │   ├── PROGRESS.md                  - Журнал прогресса (newest first) ✅
    │   ├── PROJECT_STATUS.md            - Что готово/в работе/следующее ✅
    │   └── RU_EN_GLOSSARY.md            - Глоссарий терминов
    │
    ├── 02_AI_Pipeline/                  🎨 AI ASSET GENERATION
    │   ├── AI_ASSET_PIPELINE_RA2.md     - Полный pipeline (concept→3D→UE)
    │   └── COMFYUI_WORKFLOW_RA2.md      - Setup Flux + workflows
    │
    ├── 03_Maps_Environment/             🗺️ MAPS & ENVIRONMENT
    │   ├── RA2_MAP_CONVERSION_GUIDE.md  - Конвертация карт RA2→UE5 ✅
    │   └── MAPS_ENVIRONMENT_PLAN.md     - Props, terrain, biomes
    │
    ├── 04_UI_Design/                    🎮 UI & MENUS
    │   └── RA2_MENU_UI_DESIGN.md        - Улучшенное меню RA2 🆕
    │
    ├── 05_Week_Plans/                   📅 WEEKLY ACTION PLANS
    │   ├── WEEK_2_5_ACTION_PLAN.md      - Карта + Меню + Курсор (11-17ч)
    │   └── WEEK3_BUILDINGS_PIPELINE.md  - 5 зданий (21-36ч) ✅
    │
    ├── 06_Assets_Lists/                 📦 ASSETS DATABASES
    │   └── RA2_UNITS_BUILDINGS_LIST.md  - IP-safe список всех ассетов
    │
    ├── 07_Utilities/                    🛠️ UTILITIES & HELPERS
    │   ├── LOCALIZATION.md              - Работа без английского
    │   ├── пример диаграмы.txt          - Формат схем Blueprint
    │   ├── scripts/                     - (пусто пока)
    │   └── reorganize_docs.ps1          - Скрипт реорганизации 🆕
    │
    └── UE_KB/                           📚 KNOWLEDGE BASE (unchanged)
        ├── INDEX.md                     
        ├── Editor_Basics.md
        ├── Blueprint_Basics.md
        ├── Input_Enhanced.md
        ├── Performance.md
        ├── CameraRig_RTS_Rebuild.md
        ├── CameraPawn_BP.md
        └── Edge Panning docs/ (15 файлов)
```

**Преимущества новой структуры:**
- ✅ Логическая группировка по типам
- ✅ Числовая префиксация (сортировка)
- ✅ Легко найти нужное
- ✅ Готовность к расширению

---

## 📖 ДОКУМЕНТЫ ПО КАТЕГОРИЯМ

### 🎯 Planning & Strategy (01_Planning/)

| Документ | Описание | Статус |
|----------|----------|--------|
| [TECH_SPEC.md](UE_RTS_Course/01_Planning/TECH_SPEC.md) | Техническое задание, scope, constraints | ✅ Updated |
| [ROADMAP.md](UE_RTS_Course/01_Planning/ROADMAP.md) | 12-недельный план (Gameplay-First) | ✅ Updated |
| [PROGRESS.md](UE_RTS_Course/01_Planning/PROGRESS.md) | Журнал прогресса (daily updates) | ✅ Active |
| [PROJECT_STATUS.md](UE_RTS_Course/01_Planning/PROJECT_STATUS.md) | Текущее состояние проекта | ✅ Updated |

---

### 🤖 AI & Asset Generation (02_AI_Pipeline/, 05_Week_Plans/, 06_Assets_Lists/)

| Документ | Описание | Инструменты |
|----------|----------|-------------|
| [AI_ASSET_PIPELINE_RA2.md](UE_RTS_Course/02_AI_Pipeline/AI_ASSET_PIPELINE_RA2.md) | Полный pipeline от концепта до UE5 | Flux, Hunyuan, Blender |
| [COMFYUI_WORKFLOW_RA2.md](UE_RTS_Course/02_AI_Pipeline/COMFYUI_WORKFLOW_RA2.md) | Setup ComfyUI + Flux workflows | ComfyUI |
| [WEEK3_BUILDINGS_PIPELINE.md](UE_RTS_Course/05_Week_Plans/WEEK3_BUILDINGS_PIPELINE.md) | Week 3: Генерация 5 зданий | Hunyuan 3D 2.5 ⭐ |
| [RA2_UNITS_BUILDINGS_LIST.md](UE_RTS_Course/06_Assets_Lists/RA2_UNITS_BUILDINGS_LIST.md) | IP-safe список всех ассетов | - |

**Key Tools:**
- Flux.1-dev (concepts)
- Hunyuan 3D 2.5 (3D generation) ✅ Confirmed
- Hitem3D (backup)

---

### 🗺️ Maps & Environment (03_Maps_Environment/)

| Документ | Описание | Инструменты |
|----------|----------|-------------|
| [RA2_MAP_CONVERSION_GUIDE.md](UE_RTS_Course/03_Maps_Environment/RA2_MAP_CONVERSION_GUIDE.md) | Конвертация RA2 карт → UE5 | FinalAlert2 |
| [MAPS_ENVIRONMENT_PLAN.md](UE_RTS_Course/03_Maps_Environment/MAPS_ENVIRONMENT_PLAN.md) | Props, terrain, biomes | Quixel, AI |

**Recommended Maps:**
- Heck Freezes Over (2p)
- Tour of Egypt (4p)

---

### 🎮 UI & UX Design (04_UI_Design/)

| Документ | Описание | Focus |
|----------|----------|-------|
| [RA2_MENU_UI_DESIGN.md](UE_RTS_Course/04_UI_Design/RA2_MENU_UI_DESIGN.md) 🆕 | Улучшенное меню RA2 | Main, Skirmish, HUD |

**Design Philosophy:** RA2 original + modern enhancements

---

### 📅 Week Action Plans (05_Week_Plans/)

| Week | Документ | Tasks | Time Est. |
|------|----------|-------|-----------|
| 2.5 | [WEEK_2_5_ACTION_PLAN.md](UE_RTS_Course/05_Week_Plans/WEEK_2_5_ACTION_PLAN.md) | Карта + Меню + Курсор | 11-17ч |
| 3 | [WEEK3_BUILDINGS_PIPELINE.md](UE_RTS_Course/05_Week_Plans/WEEK3_BUILDINGS_PIPELINE.md) | 5 зданий + Placement | 21-36ч |

---

### 📚 Knowledge Base (UE_KB/)

#### Core UE5:
- [INDEX.md](UE_RTS_Course/UE_KB/INDEX.md) - Указатель KB
- [Editor_Basics.md](UE_RTS_Course/UE_KB/Editor_Basics.md)
- [Blueprint_Basics.md](UE_RTS_Course/UE_KB/Blueprint_Basics.md)
- [Input_Enhanced.md](UE_RTS_Course/UE_KB/Input_Enhanced.md)
- [Performance.md](UE_RTS_Course/UE_KB/Performance.md)

#### Camera System (Week 2 ✅):
- [CameraRig_RTS_Rebuild.md](UE_RTS_Course/UE_KB/CameraRig_RTS_Rebuild.md)
- [CameraPawn_BP.md](UE_RTS_Course/UE_KB/CameraPawn_BP.md)

#### Edge Panning (Week 2 ✅):
**Implementation Guides:**
- [EdgePanning_LeftEdge_Implementation.md](UE_RTS_Course/UE_KB/EdgePanning_LeftEdge_Implementation.md)
- [EdgePanning_RightEdge_Implementation.md](UE_RTS_Course/UE_KB/EdgePanning_RightEdge_Implementation.md)
- [EdgePanning_TopBottom_Implementation.md](UE_RTS_Course/UE_KB/EdgePanning_TopBottom_Implementation.md)
- [EdgePanning_TopBottom_Detailed_RU.md](UE_RTS_Course/UE_KB/EdgePanning_TopBottom_Detailed_RU.md) - Самый детальный!

**Debugging:**
- [EdgePanning_CommonIssues_Solutions.md](UE_RTS_Course/UE_KB/EdgePanning_CommonIssues_Solutions.md)
- [EdgePanning_Debug_Guide.md](UE_RTS_Course/UE_KB/EdgePanning_Debug_Guide.md)
- [EdgePanning_DEBUG_QuickFix.md](UE_RTS_Course/UE_KB/EdgePanning_DEBUG_QuickFix.md)
- [EdgePanning_AllEdges_Fix.md](UE_RTS_Course/UE_KB/EdgePanning_AllEdges_Fix.md)
- [EdgePanning_ExecutionFlow_Fix.md](UE_RTS_Course/UE_KB/EdgePanning_ExecutionFlow_Fix.md)

**Diagrams:**
- [Blueprint_EdgePanning_Diagram.md](UE_RTS_Course/UE_KB/Blueprint_EdgePanning_Diagram.md) - ASCII схема
- [BP_EdgePanning_Implementation.md](UE_RTS_Course/UE_KB/BP_EdgePanning_Implementation.md)

---

## 🔄 WORKFLOW DEPENDENCIES

### Чтобы начать Week 2.5 нужно:
- ✅ UE5 project setup
- ✅ Camera working (DONE!)
- ⏳ FinalAlert2 установлен
- ⏳ Выбрана карта RA2

### Чтобы начать Week 3 нужно:
- ⏳ Week 2.5 завершён (карта + меню работают)
- ⏳ Flux.1-dev setup в ComfyUI
- ⏳ Hunyuan 3D 2.5 установлен
- ⏳ Blender готов к работе

---

## 📊 СТАТИСТИКА ДОКУМЕНТАЦИИ

**Всего документов:** 35+
**Категорий:** 7
**Строк кода/текста:** ~10,000+
**Последнее обновление:** 2025-10-04

**Создано за сессию 2025-10-04:**
- RA2_MENU_UI_DESIGN.md (660 строк) 🆕
- RA2_MAP_CONVERSION_GUIDE.md (615 строк)
- WEEK_2_5_ACTION_PLAN.md (715 строк)
- WEEK3_BUILDINGS_PIPELINE.md (797 строк)
- EdgePanning_TopBottom_Detailed_RU.md (345 строк)
- Обновлены: ROADMAP, PROGRESS, TECH_SPEC, PROJECT_STATUS

---

## 🔍 КАК НАЙТИ НУЖНОЕ

### "Я хочу понять с чего начать"
→ [README.md](UE_RTS_Course/01_Planning/README.md) → [ROADMAP.md](UE_RTS_Course/01_Planning/ROADMAP.md)

### "Я хочу работать прямо сейчас"
→ [WEEK_2_5_ACTION_PLAN.md](UE_RTS_Course/05_Week_Plans/WEEK_2_5_ACTION_PLAN.md)

### "Я хочу настроить AI генерацию"
→ [WEEK3_BUILDINGS_PIPELINE.md](UE_RTS_Course/05_Week_Plans/WEEK3_BUILDINGS_PIPELINE.md) (Setup Hunyuan)

### "Как конвертировать карту RA2?"
→ [RA2_MAP_CONVERSION_GUIDE.md](UE_RTS_Course/03_Maps_Environment/RA2_MAP_CONVERSION_GUIDE.md)

### "Как улучшить меню?"
→ [RA2_MENU_UI_DESIGN.md](UE_RTS_Course/04_UI_Design/RA2_MENU_UI_DESIGN.md) 🆕

### "Edge panning не работает"
→ [EdgePanning_CommonIssues_Solutions.md](UE_RTS_Course/UE_KB/EdgePanning_CommonIssues_Solutions.md)

### "Что делали вчера?"
→ [PROGRESS.md](UE_RTS_Course/01_Planning/PROGRESS.md) (newest first)

### "Что делать дальше?"
→ [PROJECT_STATUS.md](UE_RTS_Course/01_Planning/PROJECT_STATUS.md) → Section "Следующее"

---

## ⚠️ УСТАРЕВШИЕ ДОКУМЕНТЫ

**Не используй:**
- `SUMMARY.md` (корневая папка) - Устарел, см. PROGRESS.md
- `BLUEPRINT_PR_DESCRIPTION.md` - Устарел, см. Edge Panning docs в UE_KB/

**Причина:** Созданы на ранних этапах, актуальная info в новых документах.

---

## 🚀 QUICK LINKS ПО ЗАДАЧАМ

### Setup AI Tools:
1. [COMFYUI_WORKFLOW_RA2.md](UE_RTS_Course/02_AI_Pipeline/COMFYUI_WORKFLOW_RA2.md) - Flux setup
2. [WEEK3_BUILDINGS_PIPELINE.md](UE_RTS_Course/05_Week_Plans/WEEK3_BUILDINGS_PIPELINE.md) - Hunyuan 3D setup

### Создать первую карту:
1. [RA2_MAP_CONVERSION_GUIDE.md](UE_RTS_Course/03_Maps_Environment/RA2_MAP_CONVERSION_GUIDE.md) - Конвертация
2. [WEEK_2_5_ACTION_PLAN.md](UE_RTS_Course/05_Week_Plans/WEEK_2_5_ACTION_PLAN.md) - Шаг 1: Карта

### Создать меню:
1. [RA2_MENU_UI_DESIGN.md](UE_RTS_Course/04_UI_Design/RA2_MENU_UI_DESIGN.md) - Дизайн
2. [WEEK_2_5_ACTION_PLAN.md](UE_RTS_Course/05_Week_Plans/WEEK_2_5_ACTION_PLAN.md) - Шаг 2: Меню

### Отладка Edge Panning:
1. [EdgePanning_CommonIssues_Solutions.md](UE_RTS_Course/UE_KB/EdgePanning_CommonIssues_Solutions.md)
2. [EdgePanning_Debug_Guide.md](UE_RTS_Course/UE_KB/EdgePanning_Debug_Guide.md)

---

## 📝 CHANGELOG

**2025-10-04 - Major Update:**
- ✅ Created RA2_MENU_UI_DESIGN.md (660 lines)
- ✅ Updated TECH_SPEC.md (AI tools, scope clarification)
- ✅ Updated PROJECT_STATUS.md (tools confirmation)
- ✅ Created MASTER_INDEX.md (this file!)
- ✅ Confirmed AI stack: Flux + Hunyuan 3D 2.5 + Hitem3D
- ✅ Project goal clarified: RA2 Clone + Expansion

**2025-10-04 - Roadmap Reorganization:**
- ✅ Switched to Gameplay-First approach
- ✅ Week 2.5: Map + Menu + Cursor (before assets!)
- ✅ Week 3: Buildings (5 models via AI)
- ✅ Created detailed action plans

**2025-10-04 - Edge Panning Completion:**
- ✅ All 4 edges working (Left/Right/Top/Bottom)
- ✅ Parameters tuned: EdgePanSpeed=180000, BorderPx=450
- ✅ Multiple debug guides created

---

## 🎯 NEXT STEPS

**Immediate (Week 2.5):**
1. Конвертировать 1 карту RA2
2. Создать Main Menu + Skirmish Setup
3. Setup RA2 Cursor

**Short-term (Week 3):**
1. Setup Flux + Hunyuan 3D 2.5
2. Генерация 5 зданий
3. Building Placement System

**Long-term:**
- Week 4: Units + Selection
- Week 5: Economy
- Week 6: Combat

---

## ✅ SUMMARY

**Всего:** 35+ документов, ~10,000 строк
**Охват:** Planning, AI Pipeline, Maps, UI, KB
**Статус:** Актуально и maintained ✅

**Для новых разработчиков:**
Начни с [README.md](UE_RTS_Course/01_Planning/README.md) → [ROADMAP.md](UE_RTS_Course/01_Planning/ROADMAP.md) → [WEEK_2_5_ACTION_PLAN.md](UE_RTS_Course/05_Week_Plans/WEEK_2_5_ACTION_PLAN.md)

**Для продолжающих:**
См. [PROGRESS.md](UE_RTS_Course/01_Planning/PROGRESS.md) (last entry) и [PROJECT_STATUS.md](UE_RTS_Course/01_Planning/PROJECT_STATUS.md) (next tasks)

**Для реорганизации файлов:**
```powershell
cd E:\UE_red_alert_2_v001\docs\UE_RTS_Course
.\reorganize_docs.ps1
```

---

🚀 **Documentation is complete and up-to-date!**
