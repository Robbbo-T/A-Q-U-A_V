# AQUA V. Sistema de Nomenclatura v12.0
## Guía Completa de Campos y Fórmula
**Documento ID:** `AQUART-OPS-SC-POL-STD-DC-PA-NOMF-RDIG0-30400010002-MUL-PRD-EFGH5678-v12.0.0`  
**Estado:** ✅ APROBADO  
**Fecha Efectiva:** 2025-08-05  
**Clasificación:** ESTÁNDAR AQUA V. - CUMPLIMIENTO OBLIGATORIO
---
## 1. FÓRMULA COMPLETA DE NOMENCLATURA
### 1.1 Estructura General (12 campos, 79 caracteres + versión)
```
Campo:  1      2    3     4         5    6   7    8    9               10     11           12        13
       LLLLLL-PPP-SSSS-MMMMMMMM-HHH-CC-DDD-AAA-TTTTTTTTTTTTTT-RRRRR-UUUUUUUUUUU-RRR-vXX.XX.XX
       |      |    |     |         |    |   |    |    |               |     |           |        |
       LINE   PROD SUB   MSN      PHASE CRIT DOC APP  METHOD         REAL  UTCS        REG     VERSION
```
### 1.2 Longitud de Cada Campo
| Posición | Campo | Longitud | Tipo | Descripción |
|:---------|:------|:---------|:-----|:------------|
| 1 | LINE | 6 caracteres | Alfabético | Línea de producto o infraestructura |
| 2 | PROD | 3 caracteres | Alfabético | Producto o tipo de infraestructura |
| 3 | SUBPROD | 4 caracteres | Alfanumérico | Subproducto o subtipo |
| 4 | MSN | 8 caracteres | Alfanumérico | Número de serie o ID de activo |
| 5 | PHASE | 3 caracteres | Alfabético | Fase del ciclo de vida |
| 6 | CRIT | 2 caracteres | Alfabético | Criticidad de seguridad/ciber |
| 7 | DOC | 3 caracteres | Alfabético | Tipo de documento |
| 8 | APP | 3 caracteres | Alfabético | Dominio de aplicación |
| 9 | MTD | 14 caracteres | Alfanumérico | Método/Procedimiento (AA-AA-AAAA-NNNN) |
| 10 | REALIDAD | 5 caracteres | Alfabético | Contexto de efectividad |
| 11 | UTCS | 11 caracteres | Numérico | Clasificación tecnológica universal |
| 12 | REG | 3 caracteres | Alfabético | Estado regulatorio |
| 13 | VERSION | Variable | Semántico | Número de versión |
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
## 4. CAMPO 3: SUBPROD - Subproducto/Modelo (4 caracteres)
### 4.1 Subproductos AMPEL360
| Producto | Código | Subproducto | Descripción | Capacidad |
|:---------|:-------|:------------|:------------|:----------|
| BWB | Q100 | Serie Q100 | BWB Regional | 120-180 pasajeros |
| BWB | Q250 | Serie Q250 | BWB Largo alcance | 220-300 pasajeros |
| EVT | CITY | City Hopper | Movilidad urbana | 2-6 pasajeros |
| EVT | METR | Metro | Conexiones regionales | 8-12 pasajeros |
| HYB | E180 | Electric-180 | Medio alcance | 180 pasajeros |
| HYB | E220 | Electric-220 | Largo alcance | 220 pasajeros |
| SUB | SB01 | Suborbital-1 | Vehículo turístico | 6-8 pasajeros |
| SUB | SB02 | Suborbital-2 | Vehículo de investigación | 4-6 pasajeros |
| ORB | OR01 | Orbital-1 | Vehículo tripulado | 4-6 pasajeros |
| ORB | OR02 | Orbital-2 | Vehículo de carga | 2T carga útil |
### 4.2 Subproductos GAIA
| Producto | Código | Subproducto | Descripción | Aplicación |
|:---------|:-------|:------------|:------------|:-----------|
| UAV | TACT | Táctico | Operaciones militares | Defensa |
| UAV | CARG | Carga | Elevación pesada | Logística |
| UAV | HALE | Gran Altitud | Larga resistencia | Vigilancia |
| UAV | SWRM | Enjambre | Operaciones multi-unidad | Distribuido |
| SAT | QNET | Red-Q | Red cuántica | Comunicación cuántica |
| SAT | EOBS | Observación Terrestre | Imágenes | Teledetección |
| SAT | COMM | Comunicaciones | Retransmisión de datos | Conectividad |
| SAT | NAVS | Navegación | Posicionamiento | Aumento GPS |
| ROV | LUNA | Rover Lunar | Exploración lunar | Superficie lunar |
| ROV | MARS | Rover Marciano | Exploración de Marte | Superficie marciana |
| ROV | ASTE | Asteroide | Minería de asteroides | Extracción de recursos |
| CRG | LGT5 | Carga Ligera | 50kg carga útil | Última milla |
| CRG | MED5 | Carga Media | 500kg carga útil | Regional |
| CRG | HVY2 | Carga Pesada | 2T carga útil | Industrial |
| CRG | UHV5 | Ultra Pesada | 5T carga útil | Estratégico |
### 4.3 Subproductos ROBBBO-T
| Producto | Código | Subproducto | Descripción | Función |
|:---------|:-------|:------------|:------------|:--------|
| FAL | AS01 | Robot de Ensamblaje | Operaciones de ensamblaje | Producción |
| FAL | WL01 | Robot de Soldadura | Operaciones de soldadura | Unión |
| FAL | QC01 | Control de Calidad | Inspección | Pruebas |
| FAL | PT01 | Robot de Pintura | Operaciones de recubrimiento | Acabado |
| MRO | AC01 | Servicio de Aeronaves | Mantenimiento de aeronaves | Servicio en línea |
| MRO | EN01 | Servicio de Motores | Mantenimiento de motores | Revisión |
| MRO | CM01 | Servicio de Componentes | Mantenimiento de componentes | Reparación en taller |
| MRO | IN01 | Robot de Inspección | Inspección NDT | Calidad |
| SPC | EV01 | Robot EVA | Soporte de caminata espacial | Operaciones externas |
| SPC | ST01 | Robot de Estación | Estación espacial | Operaciones internas |
| SPC | CN01 | Construcción | Ensamblaje espacial | Infraestructura |
| SPC | MN01 | Robot Minero | Extracción de recursos | ISRU |
| EXP | DP01 | Mar Profundo | Exploración oceánica | Submarino |
| EXP | VL01 | Volcán | Investigación volcánica | Calor extremo |
| EXP | AR01 | Ártico | Investigación polar | Frío extremo |
| EXP | CV01 | Cueva | Exploración de cuevas | Espacio confinado |
---
## 5. CAMPO 4: MSN - Número de Serie de Manufactura (8 caracteres)
### 5.1 Formato para Productos
```
YYSSNNNN
```
- **YY**: Año (25 = 2025, 26 = 2026, etc.)
- **SS**: Código del sitio
- **NNNN**: Número secuencial (0001-9999)
### 5.2 Códigos de Sitio
| Código | Sitio | País | Especialización |
|:-------|:------|:-----|:----------------|
| MA | Madrid | España | HQ y Ensamblaje Final |
| TO | Toulouse | Francia | Aerodinámica y Certificación |
| MU | Munich | Alemania | Propulsión y Hardware Cuántico |
| NA | Nápoles | Italia | Composites y Materiales Avanzados |
| SG | Singapur | Singapur | Hub Asia y Robótica |
| SV | Silicon Valley | EE.UU. | Software y Computación Cuántica |
### 5.3 Formato para Infraestructura
```
TTTTNNNN
```
- **TTTT**: Tipo de activo
- **NNNN**: Número secuencial
### 5.4 Ejemplos de MSN
| Tipo | MSN | Descripción |
|:-----|:----|:------------|
| Aeronave | 25MAP001 | Primera aeronave fabricada en Madrid en 2025 |
| UAV | 26SGU001 | Primer UAV fabricado en Singapur en 2026 |
| Robot | 25NAR001 | Primer robot fabricado en Nápoles en 2025 |
| Infraestructura | AWSP0001 | Primera instancia AWS Producción |
| Servicio | QPAA0001 | Primera instancia de servicio QPaaS |
---
## 6. CAMPO 5: PHASE - Fase del Ciclo de Vida (3 caracteres)
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
## 7. CAMPO 6: CRIT - Criticidad de Seguridad y Ciber (2 caracteres)
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
## 8. CAMPO 7: DOC - Tipo de Documento (3 caracteres) POR FASE
### 8.1 Fase ESTRATEGIA (STR)
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
### 8.2 Fase CONCEPTUAL (CON)
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
### 8.3 Fase DISEÑO (DES)
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
### 8.4 Fase DESARROLLO Y PROTOTIPADO (DEV)
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
### 8.5 Fase PRUEBAS Y CÁLCULOS (TST)
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
### 8.6 Fase INTEGRACIÓN (INT)
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
### 8.7 Fase CERTIFICACIÓN (CRT)
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
### 8.8 Fase PRODUCCIÓN (PRD)
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
### 8.9 Fase OPERACIÓN Y SERVICIO (OPS)
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
### 8.10 Fase MANTENIMIENTO (MNT)
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
### 8.11 Fase REPARACIÓN Y RECICLAJE (REP)
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
### 8.12 Fase ACTUALIZACIÓN (UPG)
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
### 8.13 Fase EXTENSIÓN (EXT)
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
### 8.14 Fase RETIRO (RET)
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
### 8.15 Fase AUDITORÍA (AUD)
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
## 9. CAMPO 8: APP - Dominio de Aplicación (3 caracteres)
### 9.1 Para Documentos de Mantenimiento (AMM)
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
### 9.2 Para Documentos de Diseño (ICD)
| Código | Módulo | Descripción |
|:-------|:-------|:------------|
| PHY | Physical | Interfaces físicas |
| DAT | Data | Interfaces de datos |
| PWR | Power | Interfaces de potencia |
| TIM | Timing | Requisitos de temporización |
| PRO | Protocol | Protocolos de comunicación |
| ERR | Error | Manejo de errores |
| TST | Test | Interfaces de prueba |
### 9.3 Códigos Universales de Aplicación
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
## 10. CAMPO 9: MTD - Método/Procedimiento (14 caracteres)
### 10.1 Formato
```
AA-AA-AAAA-NNNN
```
- **AA**: Código de tarea (2 caracteres)
- **AA**: Código de paso (2 caracteres)  
- **AAAA**: Identificador de objeto (4 caracteres)
- **NNNN**: Número secuencial (4 dígitos)
### 10.2 Códigos de Tarea - Mantenimiento
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
### 10.3 Códigos de Paso
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
### 10.4 Códigos de Objeto (Componentes)
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
## 11. CAMPO 10: REALIDAD - Contexto de Efectividad (5 caracteres)
### 11.1 Contextos Individuales
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
### 11.2 Contextos Múltiples (MULTI)
| Código | Contexto | Descripción | Casos de Uso |
|:-------|:---------|:------------|:-------------|
| MULTI | Multicontextual | Válido en múltiples realidades | Documentos con versiones física, digital y AR |
| OMNIR | Omnirealidad | Válido en todas las realidades | Estándares universales, políticas |
| ADAPT | Adaptativo | Se ajusta según contexto | Contenido que cambia según plataforma |
### 11.3 Ejemplos de Artefactos Multicontextuales
**Manual de Mantenimiento AMM - MULTI**
```
AMPEL3-BWB-Q100-25MAP001-MNT-SE-AMM-TSG-TR-VF-E001-0001-MULTI-07150000000-MUL-v2.0.0
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
QSERVS-QPS-DIAG-QDIG0001-OPS-BC-SYS-DIA-AN-PA-DIAG-0001-ADAPT-90050000000-MUL-v3.0.0
```
Se adapta según el contexto:
- En **VRTUL**: Interfaz web completa
- En **AUGMT**: Overlay de información crítica
- En **PHYSL**: Display simplificado en panel
---
## 12. CAMPO 11: UTCS - Clasificación Tecnológica Universal (11 caracteres)
### 12.1 Formato
```
DDDCCSSPPPP
```
- **DDD**: Dominio (3 dígitos)
- **CC**: Categoría (2 dígitos)
- **SS**: Subcategoría (2 dígitos)
- **PPPP**: Tecnología específica (4 dígitos)
### 12.2 Estructura de Dominios
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
## 13. CAMPO 12: REG - Estado Regulatorio (3 caracteres)
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
## 14. CAMPO 13: ENV - Entorno Digital (3 caracteres)
| Código | Entorno | Descripción | Caso de Uso |
|:-------|:--------|:------------|:------------|
| DEV | Desarrollo | Sandbox de desarrollador | Desarrollo de características |
| TST | Pruebas | Entorno QA | Aseguramiento de calidad |
| STG | Staging | Pre-producción | Validación final |
| PRD | Producción | Sistemas en vivo | De cara al cliente |
| DRT | Prueba DR | Recuperación ante desastres | Sistemas de respaldo |
| LAB | Laboratorio | Sistemas I+D | Investigación |
| SIM | Simulación | Pruebas virtuales | Validación digital |
| TRN | Entrenamiento | Entorno de formación | Educación |
| N/A | No Aplicable | Solo físico | Elementos de hardware |
---
## 15. CAMPO 14: DSIG - Firma Digital (8 caracteres)
### 15.1 Formato
```
XXXXXXXX
```
- **XXXXXXXX**: Primeros 8 caracteres del hash SHA-256
### 15.2 Cálculo de DSIG
La firma digital se calcula como:
```
DSIG = SHA256(CAMPO1-CAMPO2-...-CAMPO13-TIMESTAMP)[0:8]
```
Donde TIMESTAMP es la fecha y hora UTC en formato ISO 8601.
### 15.3 Propósito
- Verificar integridad del documento
- Asegurar no manipulación
- Proporcionar trazabilidad
- Facilitar auditorías
---
## 16. CAMPO 15: VERSION - Versión (Variable)
### 16.1 Formato
```
vXX.XX.XX(-SUFIXO)?
```
- **v**: Literal 'v'
- **XX**: Versión mayor (cambios incompatibles)
- **XX**: Versión menor (funcionalidad compatible)
- **XX**: Versión de parche (correcciones compatibles)
- **-SUFIXO**: Sufijo opcional (alpha, beta, rc, etc.)
### 16.2 Ejemplos
- `v1.0.0` - Versión inicial
- `v2.1.3` - Versión 2 mayor, 1 menor, 3 parches
- `v3.0.0-beta.1` - Versión beta de 3.0.0
- `v1.2.0-rc.1` - Release candidate de 1.2.0
- `v2.0.1` - Corrección de parche de 2.0.0
### 16.3 Reglas de Versionado
1. Incrementar versión mayor para cambios incompatibles
2. Incrementar versión menor para funcionalidad nueva compatible
3. Incrementar versión de parche para correcciones compatibles
4. Usar sufijos para versiones de desarrollo
---
## 17. EJEMPLOS COMPLETOS
### 17.1 Ejemplo de Aeronave AMPEL360
```
AMPEL3-BWB-Q100-25MAP001-PRD-SC-COC-QUA-IN-VF-P001-0001-OPERT-02460000000-MUL-PRD-v1.0.0
```
**Desglose:**
- **AMPEL3**: Línea AMPEL360
- **BWB**: Blended Wing Body
- **Q100**: Serie Q100 (120-180 pasajeros)
- **25MAP001**: Primera unidad fabricada en Madrid en 2025
- **PRD**: Fase de Producción
- **SC**: Crítico de Seguridad
- **COC**: Certificado de Conformidad
- **QUA**: Calidad
- **IN-VF-P001-0001**: Instalación-Verificación-Parte001-Secuencia0001
- **OPERT**: Contexto Operativo (aeronave en servicio activo)
- **02460000000**: UTCS Aeroespacial-Estructuras
- **MUL**: Multi-autoridad aprobado
- **PRD**: Entorno de Producción
- **v1.0.0**: Versión inicial
### 17.2 Ejemplo de Servicio Cuántico
```
QSERVS-QPS-CORE-QPAA0001-OPS-BC-API-API-SV-PA-QAPI-0001-VRTUL-90010000000-MUL-PRD-v4.0.0
```
**Desglose:**
- **QSERVS**: Servicios Cuánticos
- **QPS**: Servicio de Procesamiento Cuántico
- **CORE**: Procesamiento Central
- **QPAA0001**: Primera instancia de servicio
- **OPS**: Fase de Operaciones
- **BC**: Crítico de Negocio
- **API**: Especificación API
- **API**: Dominio API
- **SV-PA-QAPI-0001**: Servicio-Acción Principal-QAPI-0001
- **VRTUL**: Contexto Virtual (servicio cloud)
- **90010000000**: UTCS Cuántico-Procesamiento
- **MUL**: Multi-región
- **PRD**: Producción
- **v4.0.0**: Versión 4.0.0
### 17.3 Ejemplo de Documentación con Realidad Aumentada
```
AMPEL3-BWB-Q100-25MAP001-MNT-SE-AMM-TSG-TR-VF-E001-0001-AUGMT-07150000000-MUL-PRD-v2.0.0
```
**Desglose:**
- **AMPEL3**: Línea AMPEL360
- **BWB**: Blended Wing Body
- **Q100**: Serie Q100
- **25MAP001**: Primera unidad Madrid 2025
- **MNT**: Fase de Mantenimiento
- **SE**: Esencial de Seguridad
- **AMM**: Manual de Mantenimiento
- **TSG**: Troubleshooting
- **TR-VF-E001-0001**: Troubleshoot-Verificación-Motor001-0001
- **AUGMT**: Contexto Aumentado (manual con AR para técnicos)
- **07150000000**: UTCS Aeroespacial-Motores
- **MUL**: Multi-autoridad
- **PRD**: Producción
- **v2.0.0**: Versión 2.0.0
### 17.4 Ejemplo de Sistema Sentiente
```
QSERVS-QPS-SENTN-QSNT0001-OPS-CC-SYS-AUT-AI-DE-QSEN-0001-SENTN-90030000000-PND-PRD-v1.0.0
```
**Desglose:**
- **QSERVS**: Servicios Cuánticos
- **QPS**: Servicio de Procesamiento Cuántico
- **SENTN**: Sistema Sentiente
- **QSNT0001`: Primera instancia sentiente
- **OPS**: Fase de Operaciones
- **CC**: Crítico Ciber
- **SYS**: Sistema
- **AUT**: Autónomo
- **AI-DE-QSEN-0001**: AI-Decisión-Q-Sentiente-0001
- **SENTN**: Contexto Sentiente (sistema autónomo consciente)
- **90030000000**: UTCS Cuántico-IA
- **PND**: Pendiente regulación
- **PRD**: Producción
- **v1.0.0**: Versión inicial
### 17.5 Ejemplo de Infraestructura en Standby
```
INFRAT-RIG-STRU-TESTRIG2-MNT-SI-MPS-CAL-AJ-VF-T002-0001-STAND-60010000000-N/A-TST-v1.5.0
```
**Desglose:**
- **INFRAT**: Infraestructura de Pruebas
- **RIG**: Banco de Pruebas
- **STRU**: Estructural
- **TESTRIG2**: Segundo banco de pruebas
- **MNT**: Fase de Mantenimiento
- **SI**: Importante de Seguridad
- **MPS**: Especificación de Proceso de Mantenimiento
- **CAL**: Calibración
- **AJ-VF-T002-0001**: Ajuste-Verificación-Test002-0001
- **STAND**: Contexto Standing (equipo en reserva)
- **60010000000**: UTCS Automatización-Pruebas
- **N/A**: No regulatorio
- **TST**: Entorno de pruebas
- **v1.5.0`: Versión 1.5.0
---
## 18. MATRIZ DE VALIDACIÓN
### 18.1 Validaciones Obligatorias
1. **Longitud Total**: 94 caracteres + versión
2. **LINE**: Debe ser código válido de 6 caracteres
3. **PHASE**: Debe ser una de las 15 fases válidas
4. **CRIT**: Debe tener clasificación de criticidad
5. **UTCS**: Exactamente 11 caracteres numéricos
6. **DSIG**: Exactamente 8 caracteres alfanuméricos
7. **VERSION**: Formato vX.X.X
### 18.2 Validaciones Condicionales
- Si LINE es de infraestructura → MSN usa formato de activo
- Si LINE es de producto → MSN usa formato YYSSNNNN
- Si ENV = N/A → CLOUD debe ser N/A0
- Si REALIDAD = TRPHY → ENV típicamente N/A
### 18.3 Matriz de Contextos por Fase
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
## 19. IMPLEMENTACIÓN
### 19.1 Proceso de Implementación
1. **Fase 1: Preparación (1 mes)**
   - Capacitación a administradores de sistemas
   - Actualización de bases de datos
   - Preparación de herramientas de validación
2. **Fase 2: Transición (2 meses)**
   - Implementación gradual por departamento
   - Migración de documentos existentes
   - Validación de nuevos códigos
3. **Fase 3: Operación (continuo)**
   - Uso completo del sistema
   - Auditorías periódicas
   - Mejoras continuas
### 19.2 Herramientas de Soporte
1. **Generador de Códigos**: Aplicación web para generar nomenclaturas válidas
2. **Validador Automático**: Sistema para verificar nomenclaturas existentes
3. **Base de Datos Central**: Repositorio único de todas las nomenclaturas
4. **API de Integración**: Interfaz para sistemas externos
### 19.3 Capacitación
1. **Curso Básico**: Para todos los usuarios (4 horas)
2. **Curso Avanzado**: Para administradores (8 horas)
3. **Material de Referencia**: Guías rápidas y ejemplos
4. **Soporte Continuo**: Mesa de ayuda y consultoría
---
## 20. MANTENIMIENTO DEL SISTEMA
### 20.1 Actualizaciones Periódicas
1. **Trimestrales**: Actualización de códigos de productos
2. **Semestrales**: Revisión de estructura de dominios UTCS
3. **Anuales**: Actualización mayor de versión del sistema
### 20.2 Proceso de Cambio
1. **Solicitud**: Propuesta de cambio a través de formulario
2. **Evaluación**: Análisis de impacto y viabilidad
3. **Aprobación**: Por comité de control de cambios
4. **Implementación**: Despliegue controlado
5. **Comunicación**: Notificación a todos los usuarios
### 20.3 Soporte
1. **Nivel 1**: Mesa de ayuda para consultas básicas
2. **Nivel 2**: Especialistas para problemas complejos
3. **Nivel 3**: Equipo de desarrollo para cambios del sistema
---
**FIN DEL DOCUMENTO**
© 2025 AQUA V. Aerospace. Documento Controlado.  
**Distribución:** A - Interno Ilimitado | B - Socios Autorizados | C - Autoridades Regulatorias
```

