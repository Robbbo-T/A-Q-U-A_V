# 📋 Document ID: AQUART-DES-SDS-ARC-AR-PA-N900-RDIG-304-00-01-v9.0.0 Sistema de Nomenclatura v9.0


### Desglose del Document ID:

| Campo | Valor | Significado |
|:------|:------|:------------|
| **LINE** | AQUART | Artefacto Cross-Program de AQUA V. |
| **PHASE** | DES | Design - Estamos diseñando el sistema |
| **SUBTYPE** | SDS | System Design Specification |
| **DOMAIN** | ARC | Architecture - Arquitectura del sistema |
| **MTD** | AR-PA-N900 | Architect > Primary Action > Nomenclature v9.0.0 |
| **REALITY** | RDIG | Regulated Digital (Cumplimiento obligatorio) |
| **UTCS** | 304-00-01 | Digital Architecture - Documentation Standards |
| **VERSION** | v9.0.0 | Versión 9.0.0 del sistema |

### Configuration Item:
```yaml
configuration_item:
  artifact_id: "AQUART-DES-SDS-ARC-AR-PA-N900-RDIG-304-00-01-v9.0.0"
  owner_division: "QDAT"
  owner_team: "Enterprise Architecture"
  created_by: "sarah.chen@aqua-v.aero"
  created_date: "2025-12-01T10:00:00Z"
  classification: "PUBLIC"
  lifecycle_state: "APPROVED"
```

### Extended Description:
```yaml
extended_description:
  title: "AQUA V. System Design Specification - Nomenclature System Architecture v9.0"
  short_title: "SDS - Nomenclature Architecture v9.0"
  description: "System design specification defining the next-generation naming convention and digital thread architecture for all AQUA V. artifacts. Version 9.0 introduces organizational decoupling via Configuration Items and semantic method encoding."
  keywords: ["nomenclature", "system design", "architecture", "v9.0", "digital thread", "configuration item"]
  language: "en-US"
```

Este Document ID refleja correctamente que estamos en la fase de **diseño** (DES) del sistema de nomenclatura, no en su operación.
## AQUA V. Next-Generation Naming Convention & Digital Thread Architecture

This document establishes the enhanced naming conventions for all artifacts within the AQUA V. €40 billion quantum aerospace program. Version 9.0 represents a major architectural evolution, decoupling organizational structure from artifact identification and introducing semantic method encoding for superior automation and immutability.

-----

## 🔄 v9.0 Major Enhancements

### Key Architectural Improvements:
1. **Q-Division Decoupling**: Moved from static nomenclature to dynamic Configuration Item attribute
2. **Method (MTD) Field**: Replaced generic NUMBER with semantic TASK-STEP-OBJECT encoding using **alphanumeric format**
3. **Enhanced Immutability**: Organizational changes no longer affect artifact identifiers
4. **Improved Granularity**: DOMAIN field now represents specific technical modules
5. **AI-Ready Structure**: Method encoding enables advanced automation and robotics

-----

## D.1 General Nomenclature Rule

### 🔷 Complete Nomenclature Format v9.0

The v9.0 nomenclature system maintains two mandatory components while enhancing the technical identifier:

1. **Technical Nomenclature** (Immutable identifier - 11 fields)
2. **Extended Description** (Human-readable metadata)

**Technical Nomenclature Format:**

For Product-Specific Artifacts:
```
LINE-PRODUCT-SUBPRODUCT-MSN-PHASE-SUBTYPE-DOMAIN-MTD-REALITY-UTCS-VERSION
```

For Cross-Program Artifacts:
```
AQUART-PHASE-SUBTYPE-DOMAIN-MTD-REALITY-UTCS-VERSION
```

### 🔹 Field Position Reference v9.0

| Position | Field        | Length | Type     | Required | Change from v8.0 |
|:---------|:-------------|:-------|:---------|:---------|:-----------------|
| 1        | LINE/AQUART  | 3-6    | Alpha    | ✓        | No change |
| 2        | PRODUCT      | 3      | Alpha    | ✓*       | No change |
| 3        | SUBPRODUCT   | 4      | AlphaNum | ✓*       | No change |
| 4        | MSN          | 8      | AlphaNum | ✓*       | No change |
| 5        | PHASE        | 3      | Alpha    | ✓        | No change |
| 6        | SUBTYPE      | 3      | Alpha    | ✓        | No change |
| 7        | DOMAIN       | 3      | Alpha    | ✓        | **Enhanced** |
| 8        | **MTD**      | 11     | AlphaNum | ✓        | **NEW ALPHA FORMAT** |
| 9        | REALITY      | 4      | Alpha    | ✓        | No change |
| 10       | UTCS         | 9      | Numeric  | ✓        | No change |
| ~~11~~   | ~~QD~~       | ~~4~~  | ~~Alpha~~| ~~✓~~    | **REMOVED** |
| 11       | VERSION      | 6+     | SemVer   | ✓        | Position shifted |

*Not required for AQUART artifacts

-----

## D.2 Field Definitions

### 📋 LINE - Product Line Codes

| Code | Full Name | Description | Products |
|:-----|:----------|:------------|:---------|
| AMP | AMPEL360 | Passenger aircraft systems | BWB, EVT, HYB, SUB, ORB |
| GAI | GAIA AIR & SPACE | Unmanned aerial/space systems | UAV, SAT, ROV, CRG |
| ROB | ROBBBO-T | Robotic systems | FAL, MRO, SPC, EXP |
| QUA | QUANTUM | Quantum technology systems | QPU, QCM, QSN, QSW |
| AQUART | AQUA V Artifact | Cross-program documentation | Enterprise-wide |

### 📋 PRODUCT - Product Codes

| Line | Code | Product Type | Description |
|:-----|:-----|:-------------|:------------|
| **AMP - AMPEL360** |
| | BWB | Blended Wing Body | Next-gen passenger aircraft |
| | EVT | eVTOL | Urban air mobility |
| | HYB | Hybrid-Electric | Sustainable propulsion |
| | SUB | Suborbital | Space tourism |
| | ORB | Orbital | Space access |
| **GAI - GAIA AIR & SPACE** |
| | UAV | Unmanned Aerial Vehicle | Autonomous aircraft |
| | SAT | Satellite | Space systems |
| | ROV | Rover | Planetary exploration |
| | CRG | Cargo Drone | Logistics UAV |
| **ROB - ROBBBO-T** |
| | FAL | Factory Automation Line | Manufacturing robots |
| | MRO | Maintenance Repair Overhaul | Service robots |
| | SPC | Space | Space robotics |
| | EXP | Explorer | Exploration robots |
| **QUA - QUANTUM** |
| | QPU | QPU Systems | Quantum processing units |
| | QCM | Quantum Communications | Quantum comm systems |
| | QSN | Quantum Sensors | Quantum sensing tech |
| | QSW | Quantum Software | Quantum software systems |

### 📋 SUBPRODUCT - Subproduct Codes

| Product | Code | Subproduct | Description |
|:--------|:-----|:-----------|:------------|
| **AMPEL360 Subproducts** |
| BWB | Q100 | Q100 Series | 120-180 passengers |
| BWB | Q250 | Q250 Series | 220-300 passengers |
| EVT | CITY | City Hopper | 2-6 passengers |
| EVT | METR | Metro | 8-12 passengers |
| HYB | E180 | Electric-180 | 180 passengers |
| HYB | E220 | Electric-220 | 220 passengers |
| SUB | SB01 | Suborbital-1 | 6-8 passengers |
| ORB | OR01 | Orbital-1 | 4-6 passengers |
| **GAIA Subproducts** |
| UAV | TACT | Tactical | Military ops |
| UAV | CARG | Cargo | Heavy lift |
| UAV | HALE | High Altitude | Long endurance |
| UAV | SWRM | Swarm | Multi-unit ops |
| SAT | QNET | Q-Network | Quantum network |
| SAT | EOBS | Earth Observation | Imaging |
| SAT | COMM | Communications | Data relay |
| ROV | LUNA | Lunar Rover | Moon exploration |
| ROV | MARS | Mars Rover | Mars exploration |
| CRG | LGT5 | Light Cargo | 50kg payload |
| CRG | MED5 | Medium Cargo | 500kg payload |
| CRG | HVY2 | Heavy Cargo | 2T payload |
| **ROBBBO-T Subproducts** |
| FAL | AS01 | Assembly Robot | Assembly operations |
| FAL | WL01 | Welding Robot | Welding operations |
| FAL | QC01 | Quality Control | Inspection robot |
| MRO | AC01 | Aircraft Service | Aircraft maintenance |
| MRO | EN01 | Engine Service | Engine maintenance |
| SPC | EV01 | EVA Robot | Spacewalk support |
| SPC | ST01 | Station Robot | Space station ops |
| EXP | DP01 | Deep Sea | Ocean exploration |
| EXP | VL01 | Volcano | Volcanic research |
| **QUANTUM Subproducts** |
| QPU | CORE | Core QPU | Base processor |
| QPU | EDGE | Edge QPU | Distributed |
| QPU | HYBR | Hybrid QPU | Classical-quantum |
| QCM | QKDE | QKD Encryption | Quantum key dist |
| QCM | QNET | Q-Network | Quantum internet |
| QCM | QSAT | Q-Satellite | Space quantum comm |
| QSN | QNAV | Q-Navigation | GPS-independent |
| QSN | QMAG | Q-Magnetometer | Magnetic sensing |
| QSN | QGRV | Q-Gravitometer | Gravity sensing |
| QSN | QCLK | Q-Clock | Quantum timing |
| QSN | QRAD | Q-Radar | Quantum radar |
| QSW | QALG | Q-Algorithms | Quantum algorithms |
| QSW | QSIM | Q-Simulator | Quantum simulation |
| QSW | QOPT | Q-Optimizer | Quantum optimization |

### 📋 MSN - Manufacturing Serial Number Format

Format: YYSSTNNNN

| Component | Length | Description | Example |
|:----------|:-------|:------------|:--------|
| YY | 2 | Year (25=2025) | 25 |
| SS | 2 | Site code | MA |
| T | 1 | Type code | P |
| NNNN | 4 | Sequential | 0001 |

**Site Codes:**
| Code | Location | Specialization |
|:-----|:---------|:---------------|
| MA | Madrid | Global HQ, Final Assembly |
| TO | Toulouse | Aerodynamics, Testing |
| MU | Munich | Propulsion, Quantum |
| NA | Naples | Composites, Materials |
| SG | Singapore | Asia Hub, UAV/Robotics |
| SV | Silicon Valley | Software, Quantum Computing |

**Type Codes:**
| Code | Type | Description |
|:-----|:-----|:------------|
| P | Prototype | Development prototype |
| D | Development | Test article |
| S | Series | Production unit |
| C | Customer | Customer-specific |
| Q | Quantum | Quantum-enhanced |
| R | Retrofit | Upgrade/modification |
| X | Experimental | Research platform |

### 📋 PHASE - Lifecycle Phase Codes (13 Phases)

| Code | Phase | Focus | Typical Documents |
|:-----|:------|:------|:------------------|
| CON | Conceptual | Requirements, feasibility | RQS, FAS, CDS |
| DES | Design | Specifications, models | SDS, ICD, CSP |
| DEV | Development | Implementation, code | IMP, SRC, BLD |
| TST | Testing | Validation, results | TRP, TVP, TRR |
| INT | Integration | System integration | ICR, ITP, LOG |
| CRT | Certification | Compliance, approval | CMP, AUT, REG |
| PRD | Production | Manufacturing | MPS, QCP, WIS |
| MNT | Maintenance | Service, updates | MSP, AMM, CMM |
| OPS | Operations | Procedures, performance | SOP, FOM, POL |
| REP | Repair | Fixes, modifications | FIX, MOD, SRM |
| RET | Retirement | Decommission, recycling | DIS, DCP, RCL |
| SUP | Supply Chain | Logistics, inventory | LOG, SPC, SCM |
| EXT | Extension | Upgrades, evolution | LEP, SUG, MOD |

### 📋 SUBTYPE - Document Subtype Codes

#### Conceptual Phase (CON)
| Code | Full Name | Description |
|:-----|:----------|:------------|
| RQS | Requirement Specification | System requirements |
| FAS | Feasibility Assessment | Technical feasibility |
| CDS | Conceptual Design Specification | Initial concepts |
| COP | Concept of Operations | CONOPS document |
| MRD | Market Requirements Document | Market analysis |

#### Design Phase (DES)
| Code | Full Name | Description |
|:-----|:----------|:------------|
| SDS | System Design Specification | System architecture |
| ICD | Interface Control Document | Interface definitions |
| CSP | Component Specification | Component specs |
| PRF | Performance Specification | Performance reqs |
| DVM | Design Validation Model | Validation models |

#### Development Phase (DEV)
| Code | Full Name | Description |
|:-----|:----------|:------------|
| IMP | Implementation Plan | Development planning |
| SRC | Source Code Package | Software code |
| BLD | Build Specification | Build config |
| API | API Documentation | API specs |
| SDK | Software Development Kit | Dev tools |

#### Testing Phase (TST)
| Code | Full Name | Description |
|:-----|:----------|:------------|
| TRP | Test Report | Test results |
| TVP | Test Validation Plan | Test planning |
| TRR | Test Readiness Review | Test prep review |
| TCP | Test Case Procedure | Test steps |
| TAR | Test Analysis Report | Test analysis |

#### Integration Phase (INT)
| Code | Full Name | Description |
|:-----|:----------|:------------|
| ICR | Integration Control Record | Integration tracking |
| ITP | Integration Test Plan | Integration testing |
| LOG | Integration Logbook | Integration records |
| IVR | Integration Validation Report | Integration validation |

#### Certification Phase (CRT)
| Code | Full Name | Description |
|:-----|:----------|:------------|
| CMP | Compliance Matrix | Regulatory compliance |
| AUT | Authorization Document | Cert approvals |
| REG | Regulatory Statement | Regulatory declarations |
| CER | Certification Evidence | Cert documentation |
| TSO | Technical Standard Order | TSO authorization |

#### Production Phase (PRD)
| Code | Full Name | Description |
|:-----|:----------|:------------|
| MPS | Manufacturing Process Specification | Production processes |
| QCP | Quality Control Plan | Quality procedures |
| WIS | Work Instruction Sheet | Assembly instructions |
| BOM | Bill of Materials | Parts lists |
| FAI | First Article Inspection | First unit inspection |

#### Maintenance Phase (MNT)
| Code | Full Name | Description |
|:-----|:----------|:------------|
| AMM | Aircraft Maintenance Manual | Aircraft maintenance |
| CMM | Component Maintenance Manual | Component service |
| SRM | Structural Repair Manual | Structural repairs |
| IPC | Illustrated Parts Catalog | Parts identification |
| MEL | Minimum Equipment List | Equipment requirements |
| MPD | Maintenance Planning Document | Maintenance program |
| WDM | Wiring Diagram Manual | Electrical diagrams |
| TSM | Troubleshooting Manual | Fault isolation |

#### Operations Phase (OPS)
| Code | Full Name | Description |
|:-----|:----------|:------------|
| SOP | Standard Operating Procedure | Operational procedures |
| FOM | Flight Operations Manual | Flight procedures |
| POL | Operational Policy | Operating policies |
| QMS | Quality Management System | Quality documentation |
| GOM | Ground Operations Manual | Ground procedures |

#### Repair Phase (REP)
| Code | Full Name | Description |
|:-----|:----------|:------------|
| FIX | Repair Instruction | Repair procedures |
| MOD | Modification Sheet | Modification specs |
| UPG | Upgrade Kit Description | Upgrade documentation |
| RPS | Repair Scheme | Repair planning |
| SBI | Service Bulletin Implementation | Service updates |

#### Retirement Phase (RET)
| Code | Full Name | Description |
|:-----|:----------|:------------|
| DIS | Disposal Instruction | Disposal procedures |
| DCP | Decommissioning Plan | Decommissioning process |
| RCL | Reclamation Procedure | Material recovery |
| EDS | End-of-Service Documentation | Final documentation |

#### Supply Chain Phase (SUP)
| Code | Full Name | Description |
|:-----|:----------|:------------|
| LOG | Logistics Management | Supply chain docs |
| SPC | Spare Parts Catalog | Parts inventory |
| SCM | Supply Chain Manual | Supply procedures |
| INV | Inventory Management | Inventory control |

#### Extension Phase (EXT)
| Code | Full Name | Description |
|:-----|:----------|:------------|
| LEP | Life Extension Plan | Life extension docs |
| SUG | System Upgrade Guide | Upgrade procedures |
| MOD | Modernization Document | Modernization plans |
| CAP | Capability Enhancement | Enhancement plans |

### 📋 DOMAIN - Enhanced Technical Module Codes

Domain represents specific technical modules within document subtypes, not general categories.

#### For SUBTYPE: AMM (Aircraft Maintenance Manual)
| Code | Module | Description |
|:-----|:-------|:------------|
| TSG | Troubleshooting | Fault isolation procedures |
| MPR | Maintenance Procedures | Step-by-step maintenance |
| SVC | Servicing | Fluid servicing, lubrication |
| ADJ | Adjustment | Calibration procedures |
| INS | Inspection | Visual/detailed inspection |
| TST | Testing | Functional test procedures |
| CLE | Cleaning | Cleaning procedures |
| STO | Storage | Preservation procedures |
| WGH | Weight & Balance | W&B procedures |

#### For SUBTYPE: CMM (Component Maintenance Manual)
| Code | Module | Description |
|:-----|:-------|:------------|
| DIS | Disassembly | Teardown procedures |
| ASM | Assembly | Build-up procedures |
| OVH | Overhaul | Complete overhaul |
| REP | Repair | Repair schemes |
| MOD | Modification | Upgrade procedures |
| TST | Test | Bench test procedures |
| INS | Inspection | Detailed inspection |
| PAR | Parts | Parts identification |

#### For SUBTYPE: IPC (Illustrated Parts Catalog)
| Code | Module | Description |
|:-----|:-------|:------------|
| IPL | Illustrated Parts List | Parts breakdown |
| EFF | Effectivity | Applicability data |
| INT | Interchangeability | Cross-reference |
| VEN | Vendor | Vendor codes |
| KIT | Kits | Kit contents |
| CSN | Consumables | Consumable materials |
| NHA | Next Higher Assembly | Assembly structure |

#### For SUBTYPE: SRM (Structural Repair Manual)
| Code | Module | Description |
|:-----|:-------|:------------|
| IDF | Identification | Damage identification |
| ALC | Allowable Limits | Damage limits |
| RPR | Repair | Repair procedures |
| MAT | Materials | Approved materials |
| FIN | Finishes | Surface treatment |
| INS | Inspection | Post-repair inspection |
| DAT | Data | Design data |

#### For SUBTYPE: MEL (Minimum Equipment List)
| Code | Module | Description |
|:-----|:-------|:------------|
| SYS | Systems | System-based MEL |
| CAT | Category | Dispatch categories |
| OPS | Operations | Operational procedures |
| MNT | Maintenance | Maintenance procedures |
| PLN | Planning | Repair intervals |

#### For SUBTYPE: SDS (System Design Specification)
| Code | Module | Description |
|:-----|:-------|:------------|
| ARC | Architecture | System architecture |
| REQ | Requirements | System requirements |
| INT | Interfaces | Interface definitions |
| MOD | Modes | Operating modes |
| SAF | Safety | Safety analysis |
| PER | Performance | Performance specs |
| VER | Verification | V&V requirements |

#### For SUBTYPE: ICD (Interface Control Document)
| Code | Module | Description |
|:-----|:-------|:------------|
| PHY | Physical | Physical interfaces |
| DAT | Data | Data interfaces |
| PWR | Power | Power interfaces |
| TIM | Timing | Timing requirements |
| PRO | Protocol | Communication protocols |
| ERR | Error | Error handling |
| TST | Test | Test interfaces |

#### For SUBTYPE: FOM (Flight Operations Manual)
| Code | Module | Description |
|:-----|:-------|:------------|
| NOR | Normal | Normal procedures |
| ABN | Abnormal | Abnormal procedures |
| EMG | Emergency | Emergency procedures |
| SUP | Supplementary | Supplementary procedures |
| SPL | Special | Special operations |
| APP | Appendix | Supporting data |
| PER | Performance | Performance data |

#### For SUBTYPE: WDM (Wiring Diagram Manual)
| Code | Module | Description |
|:-----|:-------|:------------|
| PWR | Power | Power distribution |
| SIG | Signal | Signal wiring |
| DAT | Data | Data bus wiring |
| GND | Ground | Grounding schemes |
| SHD | Shield | Shielding diagrams |
| CON | Connector | Connector layouts |
| PIN | Pin | Pin assignments |

#### Universal Domain Codes
| Code | Module | Description |
|:-----|:-------|:------------|
| GEN | General | General information |
| TOC | Table of Contents | Content listing |
| LEP | List of Effective Pages | Page control |
| REV | Revisions | Change record |
| ABR | Abbreviations | Acronym list |
| TEM | Temporary | Temporary procedures |
| SPL | Special | Special procedures |

### 📋 MTD - Method Field Specification

Format: AA-AA-AAAA (11 characters including hyphens)

| Component | Position | Length | Type | Description |
|:----------|:---------|:-------|:-----|:------------|
| TASK | 1-2 | 2 | Alpha | Primary task code |
| STEP | 4-5 | 2 | Alpha | Step/action code |
| OBJECT | 7-10 | 4 | AlphaNum | Object/component identifier |

#### Task Codes - Maintenance (MNT Phase)
| Code | Task | Description |
|:-----|:-----|:------------|
| RM | Remove | Removal procedures |
| IN | Install | Installation procedures |
| RP | Replace | Replacement (remove + install) |
| IS | Inspect | Inspection procedures |
| TS | Test | Testing procedures |
| AJ | Adjust | Adjustment/calibration |
| SV | Service | Servicing procedures |
| CL | Clean | Cleaning procedures |
| TR | Troubleshoot | Fault isolation |
| RR | Repair | In-situ repair |
| MD | Modify | Modification procedures |
| PS | Preserve | Storage/preservation |
| RG | Rig | Rigging procedures |
| BL | Balance | Balancing procedures |
| LB | Lubricate | Lubrication procedures |

#### Task Codes - Design (DES Phase)
| Code | Task | Description |
|:-----|:-----|:------------|
| DF | Define | Requirements definition |
| AR | Architect | System architecture |
| IF | Interface | Interface definition |
| ML | Model | 3D/CAD modeling |
| AN | Analyze | Analysis (stress, thermal) |
| SM | Simulate | Simulation activities |
| OP | Optimize | Design optimization |
| VL | Validate | Design validation |
| DC | Document | Documentation creation |
| RV | Review | Design review |

#### Task Codes - Production (PRD Phase)
| Code | Task | Description |
|:-----|:-----|:------------|
| FB | Fabricate | Part fabrication |
| AS | Assemble | Assembly operations |
| WD | Weld | Welding procedures |
| MC | Machine | Machining operations |
| CP | Composite | Composite layup |
| PT | Paint | Painting/coating |
| SI | System Install | System installation |
| CF | Configure | Configuration setup |
| PG | Program | Software loading |
| VF | Verify | Quality verification |

#### Step Codes (Universal)
| Code | Step Type | Description |
|:-----|:----------|:------------|
| PR | Preparation | Safety, tools, access |
| DC | Disconnect | Electrical, mechanical disconnection |
| AC | Access | Gaining physical access |
| PA | Primary Action | Main task execution |
| SA | Secondary Action | Supporting actions |
| VF | Verification | Check/test results |
| AJ | Adjustment | Fine-tuning |
| DM | Documentation | Recording results |
| RS | Restoration | Return to service |
| CU | Cleanup | Post-task cleanup |
| S1 | Step 1 | First sequential step |
| S2 | Step 2 | Second sequential step |
| S3 | Step 3 | Third sequential step |
| S4 | Step 4 | Fourth sequential step |
| S5 | Step 5 | Fifth sequential step |
| S6 | Step 6 | Sixth sequential step |
| S7 | Step 7 | Seventh sequential step |
| S8 | Step 8 | Eighth sequential step |
| S9 | Step 9 | Ninth sequential step |
| SX | Extended | Steps beyond 9 |

#### Object Codes (AlphaNum)
Format: AAAA (4 alphanumeric characters)

**Component Prefixes:**
- C001-C999: Connectors
- P001-P999: Parts
- A001-A999: Assemblies
- S001-S999: Systems
- M001-M999: Modules
- T001-T999: Tools

**Special Designators:**
- FC01-FC99: Fault Codes
- IF01-IF99: Installation Figures
- MF01-MF99: Maintenance Figures
- RF01-RF99: Reference Figures
- Q001-Q999: Quantum components
- X001-X999: Special/experimental

### 📋 REALITY - Reality Type Codes

| Code | Reality Type | Description | Business Model |
|:-----|:-------------|:------------|:---------------|
| PHYS | Physical/Operational | Hardware, operational systems | Asset-based |
| OPER | Operational Digital Twin | Real-time synchronized twin | Subscription |
| FDIG | Functional Digital | Operational control systems | Licensed |
| RDIG | Regulated Digital | Mandatory compliance docs | Subscription |
| GDIG | Generative Digital | AI-generated content | Pay-per-use |
| SDIG | Static Digital | Reference documentation | One-time |
| VIRT | Virtual Simulation | Predictive simulations | Usage-based |
| AUGM | Augmented Reality | AR overlays, mixed reality | Feature-based |
| ROBO | Robotic/Autonomous | Autonomous systems | Service-based |
| QASI | Quantum/Sentient AI | Advanced quantum AI | Compute-based |
| TRNS | Transpositional | Cross-reality modules | API calls |

### 📋 UTCS - Universal Technology Classification System

Format: ###-##-## (9 characters total with hyphens)

| Range | Architecture Domain | Example Chapters |
|:------|:-------------------|:-----------------|
| 000-099 | Aerospace Technology | 022=Auto Flight, 024=Electrical Power |
| 100-199 | Space Technology | 110=Structural Subsystem, 114=Propulsion |
| 200-299 | Defence Technology | 203=EW Systems, 207=Military Comms |
| 300-399 | Digital Twin/Cloud | 310=Digital Twin, 320=Machine Learning |
| 400-499 | Energy/Propulsion | 410=Chemical Propulsion, 420=Electric |
| 500-599 | Advanced Materials | 510=Carbon Fiber, 520=Advanced Composites |
| 600-699 | Ground Automation | 610=Industrial Robotics, 620=Cobots |
| 700-799 | Aerial City Viability | 701=Vertiport, 710=eVTOL Design |
| 800-899 | Cybersecurity | 810=Network Security, 870=Post-Quantum |
| 900-999 | Quantum Computing | 910=Superconducting Qubits, 950=Algorithms |

### 📋 VERSION - Semantic Versioning

Format: vMAJOR.MINOR.PATCH

**Version Components:**
- **MAJOR**: Breaking changes, incompatible updates
- **MINOR**: New features, backwards compatible
- **PATCH**: Bug fixes, minor updates

**Examples:**
- v9.0.0 - Major revision with MTD field
- v9.1.0 - Added new domain codes
- v9.1.1 - Fixed validation rule
- v9.2.0-alpha.1 - Alpha release
- v9.2.0-beta.2 - Beta release
- v9.2.0-rc.1 - Release candidate

-----

## D.3 Configuration Item Architecture

### 🗄️ Configuration Item Database Schema

```sql
CREATE TABLE configuration_items (
    artifact_id VARCHAR(100) PRIMARY KEY,
    owner_division VARCHAR(4) NOT NULL,
    owner_team VARCHAR(100),
    created_by VARCHAR(100) NOT NULL,
    created_date TIMESTAMP NOT NULL,
    last_modified_by VARCHAR(100),
    last_modified_date TIMESTAMP,
    access_level VARCHAR(20) DEFAULT 'INTERNAL',
    classification VARCHAR(20) DEFAULT 'UNCLASSIFIED',
    lifecycle_state VARCHAR(20) NOT NULL,
    
    INDEX idx_owner (owner_division, owner_team),
    INDEX idx_created (created_by, created_date),
    INDEX idx_state (lifecycle_state)
);

CREATE TABLE ownership_history (
    history_id INT AUTO_INCREMENT PRIMARY KEY,
    artifact_id VARCHAR(100) NOT NULL,
    change_date TIMESTAMP NOT NULL,
    previous_owner VARCHAR(4),
    new_owner VARCHAR(4) NOT NULL,
    changed_by VARCHAR(100) NOT NULL,
    change_reason VARCHAR(500),
    
    FOREIGN KEY (artifact_id) REFERENCES configuration_items(artifact_id),
    INDEX idx_artifact_date (artifact_id, change_date)
);
```

-----

## D.6 Examples by Product Line

### 🛩️ AMPEL360 Examples

#### BWB Q100 - Maintenance Troubleshooting
```yaml
artifact:
  nomenclature: "AMP-BWB-Q100-25MAP0001-MNT-AMM-TSG-TR-VF-FC27-RDIG-024-50-00-v9.0.0"
  configuration_item:
    owner_division: "QPOW"
```

#### eVTOL City - Component Overhaul
```yaml
artifact:
  nomenclature: "AMP-EVT-CITY-25MAP0002-MNT-CMM-OVH-RP-PA-M234-RDIG-062-00-00-v9.0.0"
  configuration_item:
    owner_division: "QMEC"
```

### 🛸 GAIA Examples

#### UAV Swarm - Interface Design
```yaml
artifact:
  nomenclature: "GAI-UAV-SWRM-25SGS0001-DES-ICD-DAT-IF-PA-S301-FDIG-308-00-00-v9.0.0"
  configuration_item:
    owner_division: "QDAT"
```

### ⚛️ QUANTUM Examples

#### Q-Navigation Calibration
```yaml
artifact:
  nomenclature: "QUA-QSN-QNAV-25MUQ0001-MNT-CMM-ADJ-AJ-VF-Q001-RDIG-938-00-00-v9.0.0"
  configuration_item:
    owner_division: "QSCI"
```

### 🤖 ROBBBO-T Examples

#### Factory Robot Assembly Procedure
```yaml
artifact:
  nomenclature: "ROB-FAL-AS01-25NAR0001-PRD-WIS-ASM-AS-PA-R123-RDIG-615-00-00-v9.0.0"
  configuration_item:
    owner_division: "QIND"
```

### 🏢 Cross-Program Examples

#### Enterprise Maintenance Planning
```yaml
artifact:
  nomenclature: "AQUART-MNT-MPD-PLN-DF-PR-X000-RDIG-005-00-00-v9.0.0"
  configuration_item:
    owner_division: "QMEC"
```

---

**Document Status:** APPROVED FOR IMPLEMENTATION  
**Version:** 9.0.0  
**Issue Date:** 2025-12-01  
**Effective Date:** 2026-01-01  
**Owner:** Chief Technology Officer
