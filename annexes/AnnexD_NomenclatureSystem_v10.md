# AQUA V. Sistema de Nomenclatura v12.3
## Guía Completa de Campos y Fórmula
**Documento ID:** `AQUART-OPS-SC-POL-STD-DC-PA-NOMF-RDIG0-30400010002-MUL-v12.3.0`  
**Estado:** ✅ APROBADO  
**Fecha Efectiva:** 2025-08-05  
**Clasificación:** ESTÁNDAR AQUA V. - CUMPLIMIENTO OBLIGATORIO
---
## 1. FÓRMULA COMPLETA DE NOMENCLATURA
### 1.1 Estructura General (12 campos, 59 caracteres + versión)
```
Campo:  1      2    3         4    5   6    7    8               9     10          11        12
       LLLLLL-PPP-XXXXXXXX-HHH-CC-DDD-AAA-TTTTTTTTTTTTTT-RRRRR-UUUUUUUUUU-RRR-vXX.XX.XX
       |      |    |         |    |   |    |    |               |     |          |        |
       LINE   PROD VARNUM    PHASE CRIT DOC APP  METHOD         REAL  UTCS       REG     VERSION
```
### 1.2 Longitud de Cada Campo
| Posición | Campo | Longitud | Tipo | Descripción |
|:---------|:------|:---------|:-----|:------------|
| 1 | LINE | 6 caracteres | Alfabético | Línea de producto o infraestructura |
| 2 | PROD | 3 caracteres | Alfabético | Producto o tipo de infraestructura |
| 3 | VARNUM | 9 caracteres | Alfanumérico | Variante y número de unidad (VVVV-NNNN) |
| 4 | PHASE | 3 caracteres | Alfabético | Fase del ciclo de vida |
| 5 | CRIT | 2 caracteres | Alfabético | Criticidad de seguridad/ciber |
| 6 | DOC | 3 caracteres | Alfabético | Tipo de documento |
| 7 | APP | 3 caracteres | Alfabético | Dominio de aplicación |
| 8 | MTD | 14 caracteres | Alfanumérico | Método/Procedimiento (AA-AA-AAAA-NNNN) |
| 9 | REALIDAD | 5 caracteres | Alfabético | Contexto de efectividad |
| 10 | UTCS | 11 caracteres | Numérico | Clasificación tecnológica universal |
| 11 | REG | 3 caracteres | Alfabético | Estado regulatorio |
| 12 | VERSION | Variable | Semántico | Número de versión |
---
## 2. CAMPO 1: LINE - Línea de Producto/Infraestructura (6 caracteres)
### 2.1 Activos de Portafolio (Generan Ingresos)
| Código | Nombre Completo | Tipo | Modelo de Ingresos |
|:-------|:----------------|:-----|:-------------------|
| AMPEL3 | AMPEL360 | Activo de Portafolio | Venta/Leasing de Aeronaves |
| GAIAIR | GAIA AIR & SPACE | Activo de Portafolio | Venta de UAV/Satélites |
| ROBBBO | ROBBBO-T | Activo de Portafolio | Venta/Servicio de Robótica |
| QSERVS | Servicios Cuánticos | Activo de Portafolio | SaaS/Licencias/Consultoría |
| QPRODS | Productos Cuánticos | Activo de Portafolio | Venta/Leasing de Hardware |
### 2.2 Infraestructura Propia (Centros de Costo)
| Código | Nombre Completo | Tipo | Centro de Costo |
|:-------|:----------------|:-----|:----------------|
| INFRAD | Infraestructura Digital | Infraestructura Propia | Operaciones TI |
| INFRAP | Infraestructura Física | Infraestructura Propia | Instalaciones |
| INFRAT | Infraestructura de Pruebas | Infraestructura Propia | I+D/Calidad |
| INFRAM | Infraestructura de Manufactura | Infraestructura Propia | Producción |
| INFRAS | Infraestructura de Seguridad | Infraestructura Propia | Operaciones de Seguridad |
| INFRAQ | Infraestructura Cuántica | Infraestructura Propia | Operaciones Cuánticas |
### 2.3 Empresa y Servicios Compartidos
| Código | Nombre Completo | Tipo | Clasificación |
|:-------|:----------------|:-----|:--------------|
| AQUART | Artefactos Cross-Programa | Empresa | Servicios Compartidos |
| SERVIC | Entrega de Servicios | Mixto | Soporte al Cliente |
| DATAPL | Plataforma de Datos | Mixto | Analytics/BI |
---
## 3. CAMPO 2: PROD - Tipo de Producto (3 caracteres)
### 3.1 Productos AMPEL360 (AMPEL3)
| Código | Producto | Descripción |
|:-------|:---------|:------------|
| BWB | Blended Wing Body | Aeronave de próxima generación |
| EVT | eVTOL | Despegue y aterrizaje vertical eléctrico |
| HYB | Híbrido-Eléctrico | Propulsión sostenible |
| SUB | Suborbital | Turismo espacial |
| ORB | Orbital | Acceso al espacio |
### 3.2 Productos GAIA (GAIAIR)
| Código | Producto | Descripción |
|:-------|:---------|:------------|
| UAV | Vehículo Aéreo No Tripulado | Aeronave autónoma |
| SAT | Satélite | Sistemas espaciales |
| ROV | Rover | Exploración planetaria |
| CRG | Dron de Carga | UAV logístico |
### 3.3 Productos ROBBBO-T (ROBBBO)
| Código | Producto | Descripción |
|:-------|:---------|:------------|
| FAL | Automatización de Fábrica | Robots de manufactura |
| MRO | Mantenimiento y Reparación | Robots de servicio |
| SPC | Espacio | Robótica espacial |
| EXP | Explorador | Robots de exploración |
### 3.4 Servicios Cuánticos (QSERVS)
| Código | Servicio | Descripción |
|:-------|:---------|:------------|
| QPS | Servicio de Procesamiento Cuántico | QPaaS |
| QKS | Servicio de Distribución de Claves | QKDaaS |
| QML | Machine Learning Cuántico | QML Cloud |
| QCN | Consultoría Cuántica | Soluciones |
### 3.5 Productos Cuánticos (QPRODS)
| Código | Producto | Descripción |
|:-------|:---------|:------------|
| QPU | Unidades de Procesamiento | Hardware cuántico |
| QKD | Dispositivos de Encriptación | Seguridad cuántica |
| QSN | Sensores Cuánticos | Detección cuántica |
| QSW | Software Cuántico | Aplicaciones |
---
## 4. CAMPO 3: VARNUM - Variante y Número de Unidad (9 caracteres)
### 4.1 Formato General
```
VVVV-NNNN
```
- **VVVV**: Código de variante (4 caracteres)
- **-**: Separador (1 carácter)
- **NNNN**: Número secuencial único (4 dígitos)

### 4.2 Ejemplos de VARNUM por Producto
#### AMPEL360
| Producto | VARNUM | Descripción | Secuencia |
|:---------|:-------|:------------|:----------|
| BWB | Q100-0001 | Primera unidad BWB Q100 | 0001 |
| BWB | Q100-0002 | Segunda unidad BWB Q100 | 0002 |
| BWB | Q250-0001 | Primera unidad BWB Q250 | 0001 |
| EVT | CITY-0001 | Primera unidad EVT CITY | 0001 |
| EVT | CITY-0015 | Quinceava unidad EVT CITY | 0015 |
| EVT | METR-0001 | Primera unidad EVT METR | 0001 |
| HYB | E180-0001 | Primera unidad HYB E180 | 0001 |
| HYB | E220-0001 | Primera unidad HYB E220 | 0001 |
| SUB | SB01-0001 | Primera unidad SUB SB01 | 0001 |
| SUB | SB02-0001 | Primera unidad SUB SB02 | 0001 |
| ORB | OR01-0001 | Primera unidad ORB OR01 | 0001 |
| ORB | OR02-0001 | Primera unidad ORB OR02 | 0001 |

#### GAIA
| Producto | VARNUM | Descripción | Secuencia |
|:---------|:-------|:------------|:----------|
| UAV | TACT-0001 | Primera unidad UAV TACT | 0001 |
| UAV | TACT-0050 | Quincuagésima unidad UAV TACT | 0050 |
| UAV | CARG-0001 | Primera unidad UAV CARG | 0001 |
| UAV | HALE-0001 | Primera unidad UAV HALE | 0001 |
| UAV | SWRM-0001 | Primera unidad UAV SWRM | 0001 |
| SAT | QNET-0001 | Primera unidad SAT QNET | 0001 |
| SAT | EOBS-0001 | Primera unidad SAT EOBS | 0001 |
| SAT | COMM-0001 | Primera unidad SAT COMM | 0001 |
| SAT | NAVS-0001 | Primera unidad SAT NAVS | 0001 |
| ROV | LUNA-0001 | Primera unidad ROV LUNA | 0001 |
| ROV | MARS-0001 | Primera unidad ROV MARS | 0001 |
| ROV | ASTE-0001 | Primera unidad ROV ASTE | 0001 |
| CRG | LGT5-0001 | Primera unidad CRG LGT5 | 0001 |
| CRG | MED5-0001 | Primera unidad CRG MED5 | 0001 |
| CRG | HVY2-0001 | Primera unidad CRG HVY2 | 0001 |
| CRG | UHV5-0001 | Primera unidad CRG UHV5 | 0001 |

#### ROBBBO-T
| Producto | VARNUM | Descripción | Secuencia |
|:---------|:-------|:------------|:----------|
| FAL | AS01-0001 | Primera unidad FAL AS01 | 0001 |
| FAL | WL01-0001 | Primera unidad FAL WL01 | 0001 |
| FAL | QC01-0001 | Primera unidad FAL QC01 | 0001 |
| FAL | PT01-0001 | Primera unidad FAL PT01 | 0001 |
| MRO | AC01-0001 | Primera unidad MRO AC01 | 0001 |
| MRO | EN01-0001 | Primera unidad MRO EN01 | 0001 |
| MRO | CM01-0001 | Primera unidad MRO CM01 | 0001 |
| MRO | IN01-0001 | Primera unidad MRO IN01 | 0001 |
| SPC | EV01-0001 | Primera unidad SPC EV01 | 0001 |
| SPC | ST01-0001 | Primera unidad SPC ST01 | 0001 |
| SPC | CN01-0001 | Primera unidad SPC CN01 | 0001 |
| SPC | MN01-0001 | Primera unidad SPC MN01 | 0001 |
| EXP | DP01-0001 | Primera unidad EXP DP01 | 0001 |
| EXP | VL01-0001 | Primera unidad EXP VL01 | 0001 |
| EXP | AR01-0001 | Primera unidad EXP AR01 | 0001 |
| EXP | CV01-0001 | Primera unidad EXP CV01 | 0001 |

#### Servicios Cuánticos
| Producto | VARNUM | Descripción | Secuencia |
|:---------|:-------|:------------|:----------|
| QPS | CORE-0001 | Primera instancia QPS CORE | 0001 |
| QPS | EDGE-0001 | Primera instancia QPS EDGE | 0001 |
| QKS | NETW-0001 | Primera instancia QKS NETW | 0001 |
| QML | CLOUD-0001 | Primera instancia QML CLOUD | 0001 |
| QCN | CONS-0001 | Primera instancia QCN CONS | 0001 |

#### Productos Cuánticos
| Producto | VARNUM | Descripción | Secuencia |
|:---------|:-------|:------------|:----------|
| QPU | Q100-0001 | Primera unidad QPU Q100 | 0001 |
| QPU | Q200-0001 | Primera unidad QPU Q200 | 0001 |
| QKD | K50-0001 | Primera unidad QKD K50 | 0001 |
| QSN | S100-0001 | Primera unidad QSN S100 | 0001 |
| QSW | SOFT-0001 | Primera unidad QSW SOFT | 0001 |

### 4.3 Formato para Infraestructura
```
TTTT-NNNN
```
- **TTTT**: Tipo de infraestructura (4 caracteres)
- **-**: Separador (1 carácter)
- **NNNN**: Número secuencial único (4 dígitos)

### 4.4 Ejemplos de VARNUM para Infraestructura
| Infraestructura | VARNUM | Descripción | Secuencia |
|:----------------|:-------|:------------|:----------|
| Digital | DIGI-0001 | Primera instancia digital | 0001 |
| Física | FISI-0001 | Primera instalación física | 0001 |
| Pruebas | PRUE-0001 | Primer banco de pruebas | 0001 |
| Manufactura | MANU-0001 | Primera línea de manufactura | 0001 |
| Seguridad | SEGU-0001 | Primer sistema de seguridad | 0001 |
| Cuántica | CUAN-0001 | Primera infraestructura cuántica | 0001 |

### 4.5 Sistema de Asignación
- **Centralizado**: Todos los VARNUM se asignan desde un sistema centralizado para garantizar unicidad global
- **Secuencial por variante**: Cada variante tiene su propia secuencia numérica
- **Sin reutilización**: Una vez asignado, un VARNUM nunca se reutiliza
- **Base de datos central**: Registro único de todos los VARNUM asignados con metadatos asociados

### 4.6 Ventajas del Nuevo Formato
- **Máxima simplificación**: Combina variante y número de unidad en un campo intuitivo
- **Identificación clara**: Formato VVVV-NNNN fácil de interpretar
- **Escalabilidad**: Soporta hasta 9,999 unidades por variante
- **Flexibilidad**: Permite adicionar nuevas variantes sin afectar la estructura
- **Consistencia**: Formato uniforme para todos los tipos de activos
---
## 5. CAMPO 4: PHASE - Fase del Ciclo de Vida (3 caracteres)
| Código | Fase | Descripción | Duración Típica |
|:-------|:-----|:------------|:----------------|
| STR | Estrategia | Planificación estratégica del negocio | 3-6 meses |
| CON | Conceptual | Requisitos y viabilidad | 6-12 meses |
| DES | Diseño | Diseño detallado y análisis | 12-24 meses |
| DEV | Desarrollo y Prototipado | Prototipado y desarrollo inicial | 12-18 meses |
| TST | Pruebas y Cálculos | Validación, verificación y cálculos | 6-12 meses |
| INT | Integración | Integración de sistemas | 3-6 meses |
| CRT | Certificación | Aprobación regulatoria | 12-24 meses |
| PRD | Producción | Fabricación y manufactura | Continuo |
| OPS | Operación y Servicio | Operaciones diarias y servicio | 20-30 años |
| MNT | Mantenimiento | Servicio y soporte técnico | Continuo |
| REP | Reparación y Reciclaje | Reparación, modificación y reciclaje | Según necesidad |
| UPG | Actualización | Mejoras mayores | 12-24 meses |
| EXT | Extensión | Extensión de vida útil | 12-24 meses |
| RET | Retiro | Fin del servicio | 6-12 meses |
| AUD | Auditoría | Verificación de cumplimiento | Periódico |
---
## 6. CAMPO 5: CRIT - Criticidad de Seguridad y Ciber (2 caracteres)
| Código | Nivel | Descripción | Requisitos de Revisión |
|:-------|:------|:------------|:-----------------------|
| SC | Crítico de Seguridad | Falla = catastrófico | Triple redundancia, métodos formales |
| SE | Esencial de Seguridad | Falla = peligroso | Revisión dual, pruebas extensivas |
| SI | Importante de Seguridad | Falla = efecto mayor | Revisión simple, pruebas estándar |
| QC | Crítico de Calidad | Impacto calidad/regulatorio | Revisión de calidad, pista de auditoría |
| CC | Crítico Ciber | Datos clasificados/SECRETO | Revisión de seguridad, encriptación |
| CS | Sensible Ciber | Datos PII/Propietarios | Revisión de privacidad, control de acceso |
| CD | Defensa Ciber | Infraestructura de seguridad | Revisión SecOps, monitoreo |
| BC | Crítico de Negocio | Impacto ingresos/operaciones | Revisión de negocio, SLA |
| NC | No Crítico | Sin impacto seguridad/ciber/negocio | Proceso estándar |
---
## 7. CAMPO 6: DOC - Tipo de Documento (3 caracteres) POR FASE
### 7.1 Fase ESTRATEGIA (STR)
| Código | Tipo de Documento | Descripción |
|:-------|:------------------|:------------|
| BSP | Business Strategy Plan | Plan estratégico de negocio |
| MKA | Market Analysis | Análisis de mercado |
| TRM | Technology Roadmap | Hoja de ruta tecnológica |
| FIN | Financial Model | Modelo financiero |
| RSK | Risk Assessment | Evaluación de riesgos |
| CMP | Competitive Analysis | Análisis competitivo |
| OPP | Opportunity Assessment | Evaluación de oportunidades |
| STK | Stakeholder Analysis | Análisis de partes interesadas |
### 7.2 Fase CONCEPTUAL (CON)
| Código | Tipo de Documento | Descripción |
|:-------|:------------------|:------------|
| ECR | Engineering Change Request | Solicitud de cambio de ingeniería |
| ECP | Engineering Change Proposal | Propuesta de cambio de ingeniería |
| PDR | Preliminary Design Review | Revisión de diseño preliminar |
| SRD | System Requirements Document | Documento de requisitos del sistema |
| FHA | Functional Hazard Assessment | Evaluación de riesgos funcionales |
| COP | Concept of Operations | Concepto de operaciones |
| FAS | Feasibility Assessment Study | Estudio de viabilidad |
| MRD | Market Requirements Document | Requisitos de mercado |
### 7.3 Fase DISEÑO (DES)
| Código | Tipo de Documento | Descripción |
|:-------|:------------------|:------------|
| CDR | Critical Design Review | Revisión de diseño crítico |
| DDR | Detailed Design Review | Revisión de diseño detallado |
| ICD | Interface Control Document | Documento de control de interfaz |
| HDD | Hardware Design Document | Documento de diseño de hardware |
| SDD | Software Design Description | Descripción de diseño de software |
| DFMEA | Design FMEA | Análisis de modos de falla de diseño |
| SDS | System Design Specification | Especificación de diseño del sistema |
| PSA | Preliminary System Safety Assessment | Evaluación preliminar de seguridad |
### 7.4 Fase DESARROLLO Y PROTOTIPADO (DEV)
| Código | Tipo de Documento | Descripción |
|:-------|:------------------|:------------|
| TRR | Test Readiness Review | Revisión de preparación para pruebas |
| PRR | Production Readiness Review | Revisión de preparación para producción |
| PSAC | Plan for Software Aspects of Certification | Plan para certificación de software |
| PHAC | Plan for Hardware Aspects of Certification | Plan para certificación de hardware |
| SRC | Source Code | Código fuente |
| EOC | Executable Object Code | Código objeto ejecutable |
| BLD | Build Specification | Especificación de construcción |
| API | API Documentation | Documentación de API |
### 7.5 Fase PRUEBAS Y CÁLCULOS (TST)
| Código | Tipo de Documento | Descripción |
|:-------|:------------------|:------------|
| QTP | Qualification Test Plan | Plan de pruebas de calificación |
| QTR | Qualification Test Report | Informe de pruebas de calificación |
| DTP | Development Test Plan | Plan de pruebas de desarrollo |
| DTR | Development Test Report | Informe de pruebas de desarrollo |
| FTP | Flight Test Plan | Plan de pruebas de vuelo |
| FTR | Flight Test Report | Informe de pruebas de vuelo |
| STR | Structural Test Report | Informe de pruebas estructurales |
| VTR | Verification Test Report | Informe de pruebas de verificación |
| CAL | Calculation Report | Informe de cálculos |
| ATR | Acceptance Test Report | Informe de pruebas de aceptación |
### 7.6 Fase INTEGRACIÓN (INT)
| Código | Tipo de Documento | Descripción |
|:-------|:------------------|:------------|
| ITP | Integration Test Plan | Plan de pruebas de integración |
| ITR | Integration Test Report | Informe de pruebas de integración |
| ICR | Integration Control Record | Registro de control de integración |
| SCMP | Software Configuration Management Plan | Plan de gestión de configuración SW |
| HCMP | Hardware Configuration Management Plan | Plan de gestión de configuración HW |
| CCB | Change Control Board Minutes | Actas del comité de control de cambios |
| IVR | Integration Validation Report | Informe de validación de integración |
| ISS | Integration System Specification | Especificación del sistema integrado |
### 7.7 Fase CERTIFICACIÓN (CRT)
| Código | Tipo de Documento | Descripción |
|:-------|:------------------|:------------|
| TC | Type Certificate | Certificado de tipo |
| STC | Supplemental Type Certificate | Certificado de tipo suplementario |
| TSO | Technical Standard Order | Orden de estándar técnico |
| PMA | Parts Manufacturer Approval | Aprobación de fabricante de partes |
| POA | Production Organization Approval | Aprobación de organización de producción |
| DOA | Design Organization Approval | Aprobación de organización de diseño |
| CMP | Compliance Matrix | Matriz de cumplimiento |
| DAS | Declaration of Design and Performance | Declaración de diseño y rendimiento |
### 7.8 Fase PRODUCCIÓN (PRD)
| Código | Tipo de Documento | Descripción |
|:-------|:------------------|:------------|
| COC | Certificate of Conformity | Certificado de conformidad |
| FAI | First Article Inspection | Inspección de primer artículo |
| PPAP | Production Part Approval Process | Proceso de aprobación de piezas |
| LOPC | Letter of Production Capability | Carta de capacidad de producción |
| CON | Concession Request | Solicitud de concesión |
| MRB | Material Review Board Report | Informe del comité de materiales |
| NCR | Nonconformance Report | Informe de no conformidad |
| BOM | Bill of Materials | Lista de materiales |
### 7.9 Fase OPERACIÓN Y SERVICIO (OPS)
| Código | Tipo de Documento | Descripción |
|:-------|:------------------|:------------|
| AFM | Aircraft Flight Manual | Manual de vuelo de aeronave |
| FCOM | Flight Crew Operating Manual | Manual de operaciones de tripulación |
| QRH | Quick Reference Handbook | Manual de referencia rápida |
| MEL | Minimum Equipment List | Lista mínima de equipamiento |
| SOP | Standard Operating Procedures | Procedimientos operativos estándar |
| CAME | Continuing Airworthiness Management Exposition | Gestión de aeronavegabilidad |
| FOM | Flight Operations Manual | Manual de operaciones de vuelo |
| GOM | Ground Operations Manual | Manual de operaciones en tierra |
### 7.10 Fase MANTENIMIENTO (MNT)
| Código | Tipo de Documento | Descripción |
|:-------|:------------------|:------------|
| AMM | Aircraft Maintenance Manual | Manual de mantenimiento de aeronave |
| CMM | Component Maintenance Manual | Manual de mantenimiento de componentes |
| SRM | Structural Repair Manual | Manual de reparación estructural |
| IPC | Illustrated Parts Catalog | Catálogo de partes ilustrado |
| MPD | Maintenance Planning Document | Documento de planificación de mantenimiento |
| SB | Service Bulletin | Boletín de servicio |
| WDM | Wiring Diagram Manual | Manual de diagramas de cableado |
| TSM | Troubleshooting Manual | Manual de resolución de problemas |
### 7.11 Fase REPARACIÓN Y RECICLAJE (REP)
| Código | Tipo de Documento | Descripción |
|:-------|:------------------|:------------|
| EO | Engineering Order | Orden de ingeniería |
| CAR | Corrective Action Request | Solicitud de acción correctiva |
| 8D | 8-Discipline Report | Informe de 8 disciplinas |
| RGA | Returned Goods Authorization | Autorización de devolución |
| CAPA | Corrective and Preventive Action | Acción correctiva y preventiva |
| NDT | Non-Destructive Test Manual | Manual de pruebas no destructivas |
| RCL | Reclamation Procedure | Procedimiento de recuperación |
| DIS | Disposal Instruction | Instrucción de eliminación |
### 7.12 Fase ACTUALIZACIÓN (UPG)
| Código | Tipo de Documento | Descripción |
|:-------|:------------------|:------------|
| UCR | Upgrade Change Request | Solicitud de cambio de actualización |
| UCP | Upgrade Change Proposal | Propuesta de cambio de actualización |
| UTR | Upgrade Test Report | Informe de prueba de actualización |
| UIP | Upgrade Installation Procedure | Procedimiento de instalación |
| UVR | Upgrade Validation Report | Informe de validación |
| UCM | Upgrade Compliance Matrix | Matriz de cumplimiento |
| USP | Upgrade Support Plan | Plan de soporte |
| UTC | Upgrade Training Course | Curso de formación |
### 7.13 Fase EXTENSIÓN (EXT)
| Código | Tipo de Documento | Descripción |
|:-------|:------------------|:------------|
| LEP | Life Extension Plan | Plan de extensión de vida |
| LEA | Life Extension Analysis | Análisis de extensión de vida |
| LER | Life Extension Report | Informe de extensión de vida |
| SLP | Service Life Program | Programa de vida de servicio |
| FCA | Fatigue Critical Areas | Áreas críticas de fatiga |
| DTA | Damage Tolerance Assessment | Evaluación de tolerancia al daño |
| EIP | Extension Inspection Program | Programa de inspección |
| ESB | Extension Service Bulletin | Boletín de servicio |
### 7.14 Fase RETIRO (RET)
| Código | Tipo de Documento | Descripción |
|:-------|:------------------|:------------|
| ECN | Engineering Change Notice | Aviso de cambio de ingeniería |
| FCN | Field Change Notice | Aviso de cambio en campo |
| BCN | Baseline Change Notice | Aviso de cambio de línea base |
| CID | Change Impact Document | Documento de impacto de cambio |
| DCN | Document Change Notice | Aviso de cambio de documento |
| DCP | Decommissioning Plan | Plan de desmantelamiento |
| EDS | End-of-Service Documentation | Documentación de fin de servicio |
| RET | Retirement Report | Informe de retiro |
### 7.15 Fase AUDITORÍA (AUD)
| Código | Tipo de Documento | Descripción |
|:-------|:------------------|:------------|
| IQA | Internal Quality Audit | Auditoría interna de calidad |
| EQA | External Quality Audit | Auditoría externa de calidad |
| SQA | Supplier Quality Audit | Auditoría de calidad de proveedores |
| PQA | Process Quality Audit | Auditoría de calidad de procesos |
| CQA | Customer Quality Audit | Auditoría de calidad del cliente |
| MR | Management Review | Revisión de gestión |
| KPI | Key Performance Indicator Report | Informe de indicadores clave |
| ACR | Audit Compliance Report | Informe de cumplimiento de auditoría |
---
## 8. CAMPO 7: APP - Dominio de Aplicación (3 caracteres)
### 8.1 Para Documentos de Mantenimiento (AMM)
| Código | Módulo | Descripción |
|:-------|:-------|:------------|
| TSG | Troubleshooting | Procedimientos de aislamiento de fallas |
| MPR | Maintenance Procedures | Mantenimiento paso a paso |
| SVC | Servicing | Servicio de fluidos, lubricación |
| ADJ | Adjustment | Procedimientos de calibración |
| INS | Inspection | Inspección visual/detallada |
| TST | Testing | Procedimientos de prueba funcional |
| CLE | Cleaning | Procedimientos de limpieza |
| STO | Storage | Procedimientos de preservación |
| WGH | Weight & Balance | Procedimientos de peso y balance |
### 8.2 Para Documentos de Diseño (ICD)
| Código | Módulo | Descripción |
|:-------|:-------|:------------|
| PHY | Physical | Interfaces físicas |
| DAT | Data | Interfaces de datos |
| PWR | Power | Interfaces de potencia |
| TIM | Timing | Requisitos de temporización |
| PRO | Protocol | Protocolos de comunicación |
| ERR | Error | Manejo de errores |
| TST | Test | Interfaces de prueba |
### 8.3 Códigos Universales de Aplicación
| Código | Aplicación | Descripción |
|:-------|:-----------|:------------|
| GEN | General | Información general |
| TOC | Table of Contents | Listado de contenidos |
| LEP | List of Effective Pages | Control de páginas |
| REV | Revisions | Registro de cambios |
| ABR | Abbreviations | Lista de acrónimos |
| TEM | Temporary | Procedimientos temporales |
| SPL | Special | Procedimientos especiales |
---
## 9. CAMPO 8: MTD - Método/Procedimiento (14 caracteres)
### 9.1 Formato
```
AA-AA-AAAA-NNNN
```
- **AA**: Código de tarea (2 caracteres)
- **AA**: Código de paso (2 caracteres)  
- **AAAA**: Identificador de objeto (4 caracteres)
- **NNNN**: Número secuencial (4 dígitos)
### 9.2 Códigos de Tarea - Mantenimiento
| Código | Tarea | Descripción |
|:-------|:------|:------------|
| RM | Remove | Procedimientos de remoción |
| IN | Install | Procedimientos de instalación |
| RP | Replace | Reemplazo (remover + instalar) |
| IS | Inspect | Procedimientos de inspección |
| TS | Test | Procedimientos de prueba |
| AJ | Adjust | Ajuste/calibración |
| SV | Service | Procedimientos de servicio |
| CL | Clean | Procedimientos de limpieza |
| TR | Troubleshoot | Aislamiento de fallas |
| RR | Repair | Reparación in-situ |
### 9.3 Códigos de Paso
| Código | Tipo de Paso | Descripción |
|:-------|:-------------|:------------|
| PR | Preparation | Seguridad, herramientas, acceso |
| DC | Disconnect | Desconexión eléctrica, mecánica |
| AC | Access | Obtener acceso físico |
| PA | Primary Action | Ejecución de tarea principal |
| SA | Secondary Action | Acciones de soporte |
| VF | Verification | Verificar/probar resultados |
| AJ | Adjustment | Ajuste fino |
| DM | Documentation | Registro de resultados |
| RS | Restoration | Retorno al servicio |
| CU | Cleanup | Limpieza post-tarea |
| S1 | Step 1 | Primer paso secuencial |
| S2 | Step 2 | Segundo paso secuencial |
| S3 | Step 3 | Tercer paso secuencial |
| S4 | Step 4 | Cuarto paso secuencial |
| S5 | Step 5 | Quinto paso secuencial |
| S6 | Step 6 | Sexto paso secuencial |
| S7 | Step 7 | Séptimo paso secuencial |
| S8 | Step 8 | Octavo paso secuencial |
| S9 | Step 9 | Noveno paso secuencial |
| SX | Extended | Pasos más allá del 9 |
### 9.4 Códigos de Objeto (Componentes)
| Prefijo | Rango | Descripción |
|:--------|:------|:------------|
| C | C001-C999 | Conectores |
| P | P001-P999 | Partes |
| F | F001-F999 | Sujetadores |
| W | W001-W999 | Cableado/Cable |
| H | H001-H999 | Mangueras |
| V | V001-V999 | Válvulas |
| S | S001-S999 | Sensores |
| M | M001-M999 | Motores |
| A | A001-A999 | Actuadores |
| B | B001-B999 | Soportes |
| L | L001-L999 | Luces |
| D | D001-D999 | Pantallas |
| R | R001-R999 | Relés |
| T | T001-T999 | Tubos |
| Q | Q001-Q999 | Componentes cuánticos |
---
## 10. CAMPO 9: REALIDAD - Contexto de Efectividad (5 caracteres)
### 10.1 Contextos Individuales
| Código | Contexto | Descripción | Dónde es Efectivo/Aplicable |
|:-------|:---------|:------------|:----------------------------|
| VRTUL | Virtual | Existe solo en entorno digital | Simuladores, software, modelos digitales |
| AUGMT | Aumentado | Superpone digital sobre físico | AR para mantenimiento, HUD, visores |
| EXTND | Extendido | Amplía capacidades físicas | Exoesqueletos, sistemas híbridos |
| SENTN | Sentiente | Sistema autónomo consciente | IA avanzada, sistemas de decisión |
| SIMUL | Simulado | Réplica digital de lo físico | Gemelos digitales, entornos de prueba |
| OPERT | Operativo | En uso activo/producción | Sistemas en servicio, equipos activos |
| STAND | Standing | En espera/almacenado | Inventario, backup, reserva |
| PHYSL | Físico | Tangible y material | Hardware, componentes, estructuras |
| HYBRD | Híbrido | Combinación física-digital | IoT, sistemas cyber-físicos |
### 10.2 Contextos Múltiples (MULTI)
| Código | Contexto | Descripción | Casos de Uso |
|:-------|:---------|:------------|:-------------|
| MULTI | Multicontextual | Válido en múltiples realidades | Documentos con versiones física, digital y AR |
| OMNIR | Omnirealidad | Válido en todas las realidades | Estándares universales, políticas |
| ADAPT | Adaptativo | Se ajusta según contexto | Contenido que cambia según plataforma |
### 10.3 Ejemplos de Artefactos Multicontextuales
**Manual de Mantenimiento AMM - MULTI**
```
AMPEL3-BWB-Q100-0001-MNT-SE-AMM-TSG-TR-VF-E001-0001-MULTI-07150000000-MUL-v2.0.0
```
Este manual existe en:
- **PHYSL**: Manual impreso en papel
- **VRTUL**: PDF/HTML en tablets
- **AUGMT**: Versión AR con HoloLens
- **SIMUL**: Integrado en simulador de entrenamiento
**Política de Seguridad - OMNIR**
```
AQUART-OPS-SC-POL-SEC-GEN-PA-POL1-0001-OMNIR-80010000000-MUL-v1.0.0
```
Esta política aplica en todos los contextos de realidad.
**Sistema de Diagnóstico - ADAPT**
```
QSERVS-QPS-CORE-0001-OPS-BC-SYS-DIA-AN-PA-DIAG-0001-ADAPT-90050000000-MUL-v3.0.0
```
Se adapta según el contexto:
- En **VRTUL**: Interfaz web completa
- En **AUGMT**: Overlay de información crítica
- En **PHYSL**: Display simplificado en panel
---
## 11. CAMPO 10: UTCS - Clasificación Tecnológica Universal (11 caracteres)
### 11.1 Formato
```
DDDCCSSPPPP
```
- **DDD**: Dominio (3 dígitos)
- **CC**: Categoría (2 dígitos)
- **SS**: Subcategoría (2 dígitos)
- **PPPP**: Tecnología específica (4 dígitos)
### 11.2 Estructura de Dominios
| Rango | Dominio | Descripción |
|:------|:--------|:------------|
| 000-099 | Aeroespacial | Tecnología aeroespacial (capítulos ATA) |
| 100-199 | Espacial | Tecnología espacial |
| 200-299 | Defensa | Tecnología de defensa |
| 300-399 | Digital/Nube | Computación digital/nube |
| 400-499 | Energía/Propulsión | Sistemas de energía |
| 500-599 | Materiales | Tecnología de materiales |
| 600-699 | Automatización | Robótica y automatización |
| 700-799 | Movilidad Urbana | UAM y transporte urbano |
| 800-899 | Ciberseguridad | Arquitectura de seguridad |
| 900-999 | Computación Cuántica | Tecnología cuántica |
---
## 12. CAMPO 11: REG - Estado Regulatorio (3 caracteres)
| Código | Autoridad | Estado | Descripción |
|:-------|:----------|:-------|:------------|
| EAS | EASA | Aprobado | Aprobación europea |
| FAA | FAA | Aprobado | Aprobación estadounidense |
| TCA | Transport Canada | Aprobado | Aprobación canadiense |
| CAS | CAAC | Aprobado | Aprobación china |
| BRA | ANAC Brasil | Aprobado | Aprobación brasileña |
| MUL | Múltiple | Multi-aprobado | Múltiples autoridades |
| PND | Pendiente | En certificación | Bajo revisión |
| N/A | No Aplicable | No requiere certificación | No regulado |
---
## 13. CAMPO 12: VERSION - Versión (Variable)
### 13.1 Formato
```
vXX.XX.XX(-SUFIXO)?
```
- **v**: Literal 'v'
- **XX**: Versión mayor (cambios incompatibles)
- **XX**: Versión menor (funcionalidad compatible)
- **XX**: Versión de parche (correcciones compatibles)
- **-SUFIXO**: Sufijo opcional (alpha, beta, rc, etc.)
### 13.2 Ejemplos
- `v1.0.0` - Versión inicial
- `v2.1.3` - Versión 2 mayor, 1 menor, 3 parches
- `v3.0.0-beta.1` - Versión beta de 3.0.0
- `v1.2.0-rc.1` - Release candidate de 1.2.0
- `v2.0.1` - Corrección de parche de 2.0.0
### 13.3 Reglas de Versionado
1. Incrementar versión mayor para cambios incompatibles
2. Incrementar versión menor para funcionalidad nueva compatible
3. Incrementar versión de parche para correcciones compatibles
4. Usar sufijos para versiones de desarrollo
---
## 14. EJEMPLOS COMPLETOS
### 14.1 Ejemplo de Aeronave AMPEL360
```
AMPEL3-BWB-Q100-0001-PRD-SC-COC-QUA-IN-VF-P001-0001-OPERT-02460000000-MUL-v1.0.0
```
**Desglose:**
- **AMPEL3**: Línea AMPEL360
- **BWB**: Blended Wing Body
- **Q100-0001**: Variante Q100, primera unidad
- **PRD**: Fase de Producción
- **SC**: Crítico de Seguridad
- **COC**: Certificado de Conformidad
- **QUA**: Calidad
- **IN-VF-P001-0001**: Instalación-Verificación-Parte001-Secuencia0001
- **OPERT**: Contexto Operativo (aeronave en servicio activo)
- **02460000000**: UTCS Aeroespacial-Estructuras
- **MUL**: Multi-autoridad aprobado
- **v1.0.0**: Versión inicial
### 14.2 Ejemplo de Servicio Cuántico
```
QSERVS-QPS-CORE-0001-OPS-BC-API-API-SV-PA-QAPI-0001-VRTUL-90010000000-MUL-v4.0.0
```
**Desglose:**
- **QSERVS**: Servicios Cuánticos
- **QPS**: Servicio de Procesamiento Cuántico
- **CORE-0001**: Variante CORE, primera instancia
- **OPS**: Fase de Operaciones
- **BC**: Crítico de Negocio
- **API**: Especificación API
- **API**: Dominio API
- **SV-PA-QAPI-0001**: Servicio-Acción Principal-QAPI-0001
- **VRTUL**: Contexto Virtual (servicio cloud)
- **90010000000**: UTCS Cuántico-Procesamiento
- **MUL**: Multi-región
- **v4.0.0**: Versión 4.0.0
### 14.3 Ejemplo de Documentación con Realidad Aumentada
```
AMPEL3-BWB-Q100-0001-MNT-SE-AMM-TSG-TR-VF-E001-0001-AUGMT-07150000000-MUL-v2.0.0
```
**Desglose:**
- **AMPEL3**: Línea AMPEL360
- **BWB**: Blended Wing Body
- **Q100-0001**: Variante Q100, primera unidad
- **MNT**: Fase de Mantenimiento
- **SE**: Esencial de Seguridad
- **AMM**: Manual de Mantenimiento
- **TSG**: Troubleshooting
- **TR-VF-E001-0001**: Troubleshoot-Verificación-Motor001-0001
- **AUGMT**: Contexto Aumentado (manual con AR para técnicos)
- **07150000000**: UTCS Aeroespacial-Motores
- **MUL**: Multi-autoridad
- **v2.0.0**: Versión 2.0.0
### 14.4 Ejemplo de Sistema Sentiente
```
QSERVS-QPS-EDGE-0002-OPS-CC-SYS-AUT-AI-DE-QSEN-0001-SENTN-90030000000-PND-v1.0.0
```
**Desglose:**
- **QSERVS**: Servicios Cuánticos
- **QPS**: Servicio de Procesamiento Cuántico
- **EDGE-0002**: Variante EDGE, segunda instancia
- **OPS**: Fase de Operaciones
- **CC**: Crítico Ciber
- **SYS**: Sistema
- **AUT**: Autónomo
- **AI-DE-QSEN-0001**: AI-Decisión-Q-Sentiente-0001
- **SENTN**: Contexto Sentiente (sistema autónomo consciente)
- **90030000000**: UTCS Cuántico-IA
- **PND**: Pendiente regulación
- **v1.0.0**: Versión inicial
### 14.5 Ejemplo de Infraestructura en Standby
```
INFRAT-PRUE-PRUE-0001-MNT-SI-MPS-CAL-AJ-VF-T002-0001-STAND-60010000000-N/A-v1.5.0
```
**Desglose:**
- **INFRAT**: Infraestructura de Pruebas
- **PRUE**: Banco de Pruebas
- **PRUE-0001**: Variante PRUE, primer banco
- **MNT**: Fase de Mantenimiento
- **SI**: Importante de Seguridad
- **MPS**: Especificación de Proceso de Mantenimiento
- **CAL**: Calibración
- **AJ-VF-T002-0001**: Ajuste-Verificación-Test002-0001
- **STAND**: Contexto Standing (equipo en reserva)
- **60010000000**: UTCS Automatización-Pruebas
- **N/A**: No regulatorio
- **v1.5.0`: Versión 1.5.0
---
## 15. MATRIZ DE VALIDACIÓN
### 15.1 Validaciones Obligatorias
1. **Longitud Total**: 74 caracteres + versión
2. **LINE**: Debe ser código válido de 6 caracteres
3. **PROD**: Debe ser código válido de 3 caracteres
4. **VARNUM**: Debe tener formato VVVV-NNNN (9 caracteres)
5. **PHASE**: Debe ser una de las 15 fases válidas
6. **CRIT**: Debe tener clasificación de criticidad
7. **UTCS**: Exactamente 11 caracteres numéricos
8. **VERSION**: Formato vX.X.X
### 15.2 Validaciones Condicionales
- Si LINE es de infraestructura → VARNUM debe usar formato de infraestructura
- Si LINE es de producto → VARNUM debe usar formato de producto
- Si REALIDAD = PHYSL → No requiere validación de entorno digital
### 15.3 Matriz de Contextos por Fase
| Fase | Contextos Típicos | Justificación |
|:-----|:------------------|:--------------|
| STR | VRTUL, SIMUL | Estrategia es conceptual |
| CON | VRTUL, SIMUL | Conceptos son virtuales |
| DES | VRTUL, SIMUL, AUGMT | Diseño usa CAD/AR |
| DEV | SIMUL, VRTUL, HYBRD | Prototipos mixtos |
| TST | SIMUL, PHYSL, HYBRD | Pruebas físicas y virtuales |
| INT | HYBRD, OPERT | Integración real |
| CRT | PHYSL, OPERT | Certificación de sistemas reales |
| PRD | PHYSL, OPERT | Producción física |
| OPS | OPERT, AUGMT | Operación con soporte AR |
| MNT | OPERT, AUGMT, STAND | Mantenimiento activo/reserva |
| REP | PHYSL, STAND | Reparación física |
| UPG | HYBRD, EXTND | Mejoras híbridas |
| EXT | OPERT, EXTND | Extensión de capacidades |
| RET | STAND, PHYSL | Retiro físico |
| AUD | VRTUL, OPERT | Auditoría digital/física |
---
## 16. IMPLEMENTACIÓN
### 16.1 Proceso de Implementación
1. **Fase 1: Preparación (1 mes)**
   - Capacitación a administradores de sistemas
   - Actualización de bases de datos
   - Preparación de herramientas de validación
   - Migración de identificadores existentes al nuevo formato VARNUM
2. **Fase 2: Transición (2 meses)**
   - Implementación gradual por departamento
   - Migración de documentos existentes
   - Validación de nuevos códigos
3. **Fase 3: Operación (continuo)**
   - Uso completo del sistema
   - Auditorías periódicas
   - Mejoras continuas
### 16.2 Herramientas de Soporte
1. **Generador de Códigos**: Aplicación web para generar nomenclaturas válidas
2. **Validador Automático**: Sistema para verificar nomenclaturas existentes
3. **Base de Datos Central**: Repositorio único de todas las nomenclaturas
4. **API de Integración**: Interfaz para sistemas externos
5. **Herramienta de Migración**: Sistema para convertir identificadores antiguos al nuevo formato
### 16.3 Capacitación
1. **Curso Básico**: Para todos los usuarios (4 horas)
2. **Curso Avanzado**: Para administradores (8 horas)
3. **Material de Referencia**: Guías rápidas y ejemplos
4. **Soporte Continuo**: Mesa de ayuda y consultoría
---
## 17. MANTENIMIENTO DEL SISTEMA
### 17.1 Actualizaciones Periódicas
1. **Trimestrales**: Actualización de códigos de productos
2. **Semestrales**: Revisión de estructura de dominios UTCS
3. **Anuales**: Actualización mayor de versión del sistema
### 17.2 Proceso de Cambio
1. **Solicitud**: Propuesta de cambio a través de formulario
2. **Evaluación**: Análisis de impacto y viabilidad
3. **Aprobación**: Por comité de control de cambios
4. **Implementación**: Despliegue controlado
5. **Comunicación**: Notificación a todos los usuarios
### 17.3 Soporte
1. **Nivel 1**: Mesa de ayuda para consultas básicas
2. **Nivel 2**: Especialistas para problemas complejos
3. **Nivel 3**: Equipo de desarrollo para cambios del sistema
---
**FIN DEL DOCUMENTO**
© 2025 AQUA V. Aerospace. Documento Controlado.  
**Distribución:** A - Interno Ilimitado | B - Socios Autorizados | C - Autoridades Regulatorias

