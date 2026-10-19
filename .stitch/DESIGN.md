---
name: Telemetry Node Mesh
colors:
  surface: '#0e141d'
  surface-dim: '#0e141d'
  surface-bright: '#343944'
  surface-container-lowest: '#080e17'
  surface-container-low: '#161c25'
  surface-container: '#1a2029'
  surface-container-high: '#242a34'
  surface-container-highest: '#2f353f'
  on-surface: '#dde2f0'
  on-surface-variant: '#bbcac6'
  inverse-surface: '#dde2f0'
  inverse-on-surface: '#2b313b'
  outline: '#859490'
  outline-variant: '#3c4947'
  surface-tint: '#4fdbc8'
  primary: '#4fdbc8'
  on-primary: '#003731'
  primary-container: '#14b8a6'
  on-primary-container: '#00423b'
  inverse-primary: '#006b5f'
  secondary: '#ffb95f'
  on-secondary: '#472a00'
  secondary-container: '#ee9800'
  on-secondary-container: '#5b3800'
  tertiary: '#ffb3ad'
  on-tertiary: '#68000a'
  tertiary-container: '#ff7d76'
  on-tertiary-container: '#7b000e'
  error: '#ffb4ab'
  on-error: '#690005'
  error-container: '#93000a'
  on-error-container: '#ffdad6'
  primary-fixed: '#71f8e4'
  primary-fixed-dim: '#4fdbc8'
  on-primary-fixed: '#00201c'
  on-primary-fixed-variant: '#005048'
  secondary-fixed: '#ffddb8'
  secondary-fixed-dim: '#ffb95f'
  on-secondary-fixed: '#2a1700'
  on-secondary-fixed-variant: '#653e00'
  tertiary-fixed: '#ffdad7'
  tertiary-fixed-dim: '#ffb3ad'
  on-tertiary-fixed: '#410004'
  on-tertiary-fixed-variant: '#930013'
  background: '#0e141d'
  on-background: '#dde2f0'
  surface-variant: '#2f353f'
typography:
  headline-xl:
    fontFamily: Geist
    fontSize: 2rem
    fontWeight: '600'
    lineHeight: 2.5rem
    letterSpacing: -0.02em
  headline-xl-mobile:
    fontFamily: Geist
    fontSize: 1.5rem
    fontWeight: '600'
    lineHeight: 2rem
    letterSpacing: -0.015em
  headline-lg:
    fontFamily: Geist
    fontSize: 1.5rem
    fontWeight: '600'
    lineHeight: 2rem
    letterSpacing: -0.015em
  headline-lg-mobile:
    fontFamily: Geist
    fontSize: 1.25rem
    fontWeight: '600'
    lineHeight: 1.75rem
    letterSpacing: -0.01em
  headline-md:
    fontFamily: Geist
    fontSize: 1.125rem
    fontWeight: '500'
    lineHeight: 1.5rem
    letterSpacing: -0.01em
  body-lg:
    fontFamily: Geist
    fontSize: 1rem
    fontWeight: '400'
    lineHeight: 1.5rem
  body-md:
    fontFamily: Geist
    fontSize: 0.875rem
    fontWeight: '400'
    lineHeight: 1.25rem
  body-sm:
    fontFamily: Geist
    fontSize: 0.75rem
    fontWeight: '400'
    lineHeight: 1rem
  label-lg:
    fontFamily: JetBrains Mono
    fontSize: 0.875rem
    fontWeight: '500'
    lineHeight: 1.25rem
    letterSpacing: 0.02em
  label-md:
    fontFamily: JetBrains Mono
    fontSize: 0.75rem
    fontWeight: '500'
    lineHeight: 1rem
    letterSpacing: 0.03em
  label-sm:
    fontFamily: JetBrains Mono
    fontSize: 0.6875rem
    fontWeight: '400'
    lineHeight: 0.875rem
    letterSpacing: 0.04em
  metric-display:
    fontFamily: JetBrains Mono
    fontSize: 2rem
    fontWeight: '600'
    lineHeight: 2.25rem
    letterSpacing: -0.02em
  metric-display-mobile:
    fontFamily: JetBrains Mono
    fontSize: 1.5rem
    fontWeight: '600'
    lineHeight: 1.75rem
    letterSpacing: -0.01em
rounded:
  sm: 0.125rem
  DEFAULT: 0.25rem
  md: 0.375rem
  lg: 0.5rem
  xl: 0.75rem
  full: 9999px
spacing:
  gutter: 1rem
  gutter-desktop: 1.5rem
  margin: 1rem
  margin-desktop: 2rem
  space-xs: 0.25rem
  space-sm: 0.5rem
  space-md: 1rem
  space-lg: 1.5rem
  space-xl: 2rem
---

## Brand & Style

This design system is engineered for mission-critical, continuous real-time monitoring of distributed IoT edge environments (ESP32 sensor clusters). The personality is utilitarian, austere, vigilant, and calm. It avoids speculative sci-fi tropes, glowing neon skeuomorphism, and non-functional visual noise in favor of high-legibility telemetry, spatial density, and immediate situational awareness.

The design movement is **Structured Technical Minimalism** crossed with industrial instrumentation. Visual hierarchy is established strictly through tonal surface layering, calibrated state contrast, and rigorous tabular alignment. Operators monitoring dense node clusters must experience zero visual fatigue during 24/7 cycles; thus, interface elements default to restrained, low-luminance slate-navy values, allowing live system states and alert signals to surface with unambiguous clarity. Every state indicator pairs chromatic encoding with explicit iconography and text labels to satisfy WCAG AA requirements and prevent state confusion.

## Colors

The palette operates under a calibrated dark regime structured to minimize eye strain while maintaining precise contrast ratios for critical readings.

### Palette Architecture
- **Base Canvas (`#0B111A`)**: Fundamental application backdrop behind all modular panels and network maps.
- **Surface Layer 1 (`#111A26`)**: Card and module background panels.
- **Surface Layer 2 (`#192434`)**: Nested telemetry panels, table rows, input fields, and metric readouts.
- **Surface Layer 3 (`#243347`)**: Hover states, active tabs, floating popovers, and header bars.
- **Structural Lines (`#27374D` / `#33445C`)**: Clean, low-contrast hairline borders isolating data cells without visual weight.

### Semantic Telemetry States
Never deploy chromatic accents as ambient decoration, backdrop glows, or multi-stop gradients. Colors signify operational hardware states:
- **Nominal / Live**: Precision Teal (`#14B8A6`), interactive hover (`#0D9488`), and high-legibility readout contrast (`#2DD4BF`). Indicates synchronized nodes, active packet transmission, and nominal sensor bounds.
- **Warning / Degraded**: Amber (`#F59E0B`), active border (`#D97706`). Indicates packet drops, battery voltage drop (<3.3V), or marginal environmental thresholds.
- **Critical / Offline**: Crimson (`#EF4444`), edge warning (`#DC2626`). Indicates stale nodes (>3 missed heartbeats), hardware brownouts, or critical threshold breaches.

### Text Hierarchy
- **Text Primary (`#F1F5F9`)**: Telemetry figures, active titles, and critical alerts.
- **Text Secondary (`#94A3B8`)**: Sensor labels, column headers, units of measurement, and timestamps.
- **Text Muted / Tertiary (`#64748B`)**: Inactive controls, hex addresses, MAC IDs, and structural grid guides.

## Typography

Typography prioritizes rapid scannability and structural alignment under fluctuating values.

### Typeface Roles
- **Geist (Body & Structural Display)**: Applied for global interface framing, panel titles, narrative logs, and status explanations. It provides clean neo-grotesque proportions with neutral architecture.
- **JetBrains Mono (Telemetry & Metrics)**: Mandatory for all streaming numerical data, sensor units, MAC/IP addresses, payload hex monitors, and tabular grids. Numeric figures must render with fixed-width glyphs (`font-variant-numeric: tabular-nums`) to prevent layout shifts during live data ticks.

### Style Directives
- Telemetry units (e.g., `°C`, `hPa`, `PPM`, `dBm`) sit adjacent to metric readouts formatted using `label-md` in `#94A3B8`.
- Section headers rely on subdued uppercase tracking: `0.04em` letter-spacing rendered through `label-sm`.

## Layout & Spacing

The layout is constructed on an exact 8-point spatial rhythm (with 4px baseline sub-increments for compact telemetry data rows).

### Grid System
- **Desktop (≥ 1280px)**: 12-column fluid grid, `2rem` (32px) margins, `1.5rem` (24px) gutters. Complex dashboards support multi-column sensor arrays (e.g., 3-column metric cards, 9-column interactive mesh topology graph).
- **Tablet (768px – 1279px)**: 8-column layout, `1.5rem` (24px) margins, `1rem` (16px) gutters. Ancillary inspection drawers fold into dismissible split-sheets.
- **Mobile (< 768px)**: 4-column layout, `1rem` (16px) margins and gutters. Sensor panels stack vertically; data density shifts to horizontally scrollable data lists with sticky primary identifiers.

### Spacing Usage
- `space-xs` (4px): Gap between numerical readout and unit tag; interior padding of micro status chips.
- `space-sm` (8px): Gap between metadata rows; padding inside inputs and compact table cells.
- `space-md` (16px): Standard internal card padding; gap between sibling modules.
- `space-lg` (24px): Padding within primary telemetry sections and container dividers.
- `space-xl` (32px): Major sectional vertical spacing.

## Elevation & Depth

This system intentionally rejects skeuomorphic shadows, ambient colored blurs, and glassmorphism. Visual depth is established through a strict **Tonal Layer Model** reinforced with low-contrast structural borders.

### Depth Architecture
- **Layer 0 (Canvas Base - `#0B111A`)**: Baseline background; receives zero shadow or border styling.
- **Layer 1 (Card / Dashboard Module - `#111A26`)**: Encased in a `1px` continuous perimeter border of `#27374D`. No box shadow is applied.
- **Layer 2 (Nested Block / Data Cell - `#192434`)**: Sub-surfaces within modules (e.g., table headers, graph canvases, sparkline frames). Border is `1px` solid `#27374D`.
- **Layer 3 (Overlay / Modal / Flyout - `#243347`)**: Transient layers (node debug modals, configuration dropdowns). Border is elevated to `1px` solid `#33445C`, complemented by a directional ambient shadow: `0 8px 24px -4px rgba(3, 7, 18, 0.6)`.

### Border Discipline
Dividers between contiguous horizontal nodes use `1px` solid `#27374D`. Under no circumstances should borders use bright saturated colors unless denoting an active, unbroken warning or alarm state across the entire module.

## Shapes

The design uses a tight, industrial corner radius reflecting precision instrumentation.

### Corner Radii Guidelines
- **Core Components (`rounded-sm` / 4px)**: Input fields, buttons, node chips, inline badges, and metric containers.
- **Card Panels (`rounded-md` / 8px)**: Primary grid cards, topology maps, charting containers, and modal sheets.
- **Pills / Circles (`rounded-full`)**: Restricted strictly to status dot indicators (6px or 8px hardware state LEDs) and pagination counters.
- **Sharp Radii (0px)**: Adjacent data tables, continuous segmented toolbars, and grouped toggle switches where interior borders share common edges.

## Components

### Buttons
- **Primary / Action**: Background `#14B8A6`, text `#0B111A` (bold, high-contrast black on teal), radius 4px, height 36px. Hover: `#0D9488`. Active focus: 2px offset border in `#2DD4BF`.
- **Secondary / Surface**: Background `#192434`, border 1px solid `#33445C`, text `#F1F5F9`. Hover: background `#243347`, border `#94A3B8`.
- **Destructive**: Background `#192434`, border 1px solid `#DC2626`, text `#EF4444`. Hover: background `#EF4444`, text `#FFFFFF`.
- **Icon Buttons**: Fixed 32x32px or 36x36px square with 4px radius, housing 16px geometric monochrome stroke icons.

### Badges & Status Chips
- Always combine a 6px solid circular indicator, a text descriptor, and an optional numeric value.
- **Nominal State**: Background `#111A26`, border 1px solid `#14B8A6`, text `#2DD4BF`. Dot: `#14B8A6`.
- **Warning State**: Background `#111A26`, border 1px solid `#F59E0B`, text `#F59E0B`. Dot: `#F59E0B`.
- **Critical / Stale State**: Background `#111A26`, border 1px solid `#EF4444`, text `#EF4444`. Dot: `#EF4444`.

### Metric & Telemetry Cards
- Enclosed in `#111A26` with a `1px` border of `#27374D`.
- Layout: 
  1. Top header row: Sensor ID / Metric Label (`label-md` in `#94A3B8`) paired with a node status indicator chip.
  2. Main body: Massive tabular numeric value (`metric-display` in `#F1F5F9`) aligned with the unit token (`label-md` in `#64748B`).
  3. Footer: Trend micro-sparkline or timestamp delta (e.g., `LAST TX: 124ms AGO`) in `JetBrains Mono` 11px `#64748B`.

### Tables & Data Grids
- **Header**: Height 36px, background `#111A26`, text `label-sm` uppercase `#64748B`, border-bottom 1px solid `#27374D`.
- **Row**: Height 44px, alternating background `#0B111A` and `#111A26`, hover background `#192434`. Border-bottom 1px solid `#192434`.
- **Cell Alignment**: Telemetry numbers and timestamps right-aligned; text descriptors and node labels left-aligned; status chips centered.

### Inputs & Sensor Controls
- Text inputs and dropdowns use background `#111A26`, border 1px solid `#27374D`, text `#F1F5F9`, height 36px, 4px radius.
- **Focus**: Border `#14B8A6` with zero outer glow.
- **Checkboxes & Radios**: 16x16px square/circle, border 1px solid `#33445C`, background `#0B111A`. When checked, filled with `#14B8A6` with a `#0B111A` checkmark/dot.

### Network Topology Node Indicators
- Node visual representation on the mesh canvas: 28x28px dark square (`#192434`) with a 1px border colored according to health (`#14B8A6`, `#F59E0B`, `#EF4444`).
- Connected links render as 1px vector paths colored `#27374D`; degraded routes use dashed stroke configurations rather than color alone.
