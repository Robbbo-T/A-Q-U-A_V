<!-- AQUA V. v12.3 Compliant -->

<!-- Artifact ID: AQUART-OPS-BC-POL-TRN-DF-PA-TRNS-0001-SDIG-00100000000-N/A-v12.3.0 -->

```yaml
artifact:
  nomenclature: "AQUART-OPS-BC-POL-TRN-DF-PA-TRNS-0001-SDIG-00100000000-N/A-v12.3.0"
  configuration_item:
    artifact_id: "AQUART-OPS-BC-POL-TRN-DF-PA-TRNS-0001-SDIG-00100000000-N/A-v12.3.0"
    owner_division: "QDAT"
    owner_team: "Enterprise Standards & Governance"
    created_by: "apelliccia (validated by AGEN-QAI)"
    created_date: "2025-12-03T09:35:00Z"
    classification: "AQUA V. STANDARD – MANDATORY COMPLIANCE"
    lifecycle_state: "APPROVED"
  extended_description:
    title: "AQUA V. Enterprise Operational Policy - Training and Development Programs Standard"
    short_title: "Enterprise POL - Training & Development"
    description: "Defines the enterprise-wide methodology, governance model, and minimum technical requirements for designing, delivering, and maintaining training and certification programs across all AQUA V. Q-Divisions."
    keywords: ["training", "learning", "certification", "competency", "lms", "policy", "standard"]
    language: "en-US"
    translations:
      - language: "es-ES"
        title: "Política Operacional Empresarial - Estándar de Programas de Formación y Desarrollo"
```

# Annex I: Training and Development Programs Standard

|                    |                                                                      |
| :----------------- | :------------------------------------------------------------------- |
| **Document Title** | Training and Development Programs Standard                           |
| **Artifact ID**    | `AQUART-OPS-BC-POL-TRN-DF-PA-TRNS-0001-SDIG-00100000000-N/A-v12.3.0` |
| **Phase**          | OPS – Operations                                                     |
| **Owner Division** | QDAT – Enterprise Standards & Governance                             |
| **Status**         | ✅ APPROVED                                                           |
| **Version**        | v12.3.0                                                              |
| **Authorship**     | Validated by AGEN-QAI and Amedeo Pelliccia                           |

---

## Table of Contents

1. [Purpose & Scope](#1-purpose--scope)
2. [Governance Principles](#2-governance-principles)
3. [Training Lifecycle Model](#3-training-lifecycle-model)
4. [Program Design Requirements](#4-program-design-requirements)
5. [Delivery Platforms & Modalities](#5-delivery-platforms--modalities)
6. [Assessment & Certification](#6-assessment--certification)
7. [Change & Continuous-Improvement Process](#7-change--continuous-improvement-process)
8. [Appendix: Q-Division Skill Matrix](#8-appendix-q-division-skill-matrix)

---

## 1. Purpose & Scope

### 1.1 Purpose

This standard establishes the mandatory enterprise methodology for creating, delivering, and maintaining all training and development programs within AQUA V. It ensures that personnel across every Q-Division achieve and sustain the competencies required for safety, quality, security, and business performance.

### 1.2 Scope

* **Applies to:** All instructor-led, e-learning, XR-based, and blended courses delivered to AQUA V. employees, contractors, and partners. All certification schemes where AQUA V. is the certifying body.
* **Does not apply to:** Informal peer-to-peer knowledge sharing or non-integrated vendor product familiarization.

---

## 2. Governance Principles

* **Alignment to Business Objectives:** Every training artifact SHALL map to a strategic objective, safety requirement, or regulatory mandate.
* **Evidence-Based Design:** Course content SHALL be derived from formal Job Task Analysis (JTA), performance data, and incident metrics.
* **Single Source of Truth:** All official learning objects SHALL reside in the enterprise Learning Management System (LMS) and be version-controlled with a unique `v12.3` artifact ID.
* **XR-Ready by Default:** New modules SHALL include assets (3D models, AR markers) enabling deployment to `VIRT`/`AUGM` realities when relevant.
* **Accessibility & Inclusion:** Content SHALL meet WCAG 2.2 Level AA standards.

---

## 3. Training Lifecycle Model

The following official AQUA V. lifecycle phases SHALL be used for all training development. The legacy ADDIE model is deprecated.

| Phase Code | Phase Name  | Training-Context Focus                   | Key Artifacts (Examples)              |
| :--------- | :---------- | :--------------------------------------- | :------------------------------------ |
| **STR**    | Strategy    | Training need identification & analysis  | Job Task Analysis (JTA), Risk Map     |
| **CON**    | Conceptual  | High-level solution design & feasibility | Course Blueprint, Assessment Strategy |
| **DES**    | Design      | Detailed course blueprint & storyboards  | `...-DES-NC-PLN-TRN-...`              |
| **DEV**    | Development | Content production & pilot package       | SCORM/xAPI Package, Instructor Guide  |
| **OPS**    | Operations  | Live delivery & continuous support       | LMS Course, XR Manifest               |
| **AUD**    | Audit       | Post-delivery performance evaluation     | Level 1-4 Evaluation Report, CAPA Log |

---

## 4. Program Design Requirements

* **Learning Objectives:** Must be SMART (Specific, Measurable, Achievable, Relevant, Time-bound) and aligned to Bloom’s Taxonomy level ≥ Apply.
* **XR Asset Specs:** 3D models SHALL be GLTF 2.0; textures ≤ 4K; voice-over in WAV 48 kHz.
* **Metadata:** Each learning object SHALL include UTCS code, language, duration, required proficiency level, and `REALIDAD` tags (`SDIG`, `VIRT`, `AUGM`).

---

## 5. Delivery Platforms & Modalities

| Platform        | REALIDAD  | Primary Use                   | SCORM / xAPI   | Offline Support |
| :-------------- | :-------- | :---------------------------- | :------------- | :-------------- |
| **AQUA-LMS**    | SDIG      | e-learning, assessments       | SCORM 2004 4th | ✓ HTML5 ZIP     |
| **AQUA-XR Hub** | VIRT/AUGM | Immersive sims, digital twins | xAPI (cmi5)    | ✗               |
| **Mobile LXP**  | SDIG/AUGM | Micro-learning, AR job aids   | xAPI           | ✓ PWA Cache     |

All platforms SHALL authenticate via the AQUA V. identity federation using OIDC tokens.

---

## 6. Assessment & Certification

* **Assessment Design:** Minimum 10 items per learning objective; mix of MCQ, practical task, and scenario-based questions.
* **Pass Mark:** Default 80% unless dictated higher by regulation.
* **Proctoring:** High-stakes exams (`CRIT: SC, SE, CC`) SHALL use AI/ML proctoring.
* **Certificate ID:** Generated per `AQUA-Cert Schema 1.2`, embedding UTCS and reality codes.
* **Recertification:** Business-critical roles (`CRIT: BC`) require refresher training every 24 months.

---

## 7. Change & Continuous-Improvement Process

1. **Trigger:** Regulation change, incident RCA, or KPI shortfall.
2. **Request:** L\&D Quality Analyst raises a Curriculum Change Request (CCR) artifact.
3. **Design & Development:** Content team amends modules following the lifecycle in §3.
4. **Review:** SMEs and relevant boards sign-off within the LMS workflow.
5. **Release:** Version bump and delta-training notification pushed enterprise-wide.
6. **Monitor:** Key KPIs include Completion Rate (≥98%), First-Time Pass Rate (≥90%), and Behavior Adoption Index (≥75%).

---

## 8. Appendix: Q-Division Skill Matrix

| Skill Cluster      | QSTR | QPOW | QHPC | QIND | QMEC | QDAT |
| :----------------- | :--- | :--- | :--- | :--- | :--- | :--- |
| Safety Management  | A    | A    | B    | B    | A    | B    |
| Quantum Systems    | C    | B    | A    | C    | C    | B    |
| Advanced Materials | B    | A    | C    | A    | B    | C    |
| XR Operations      | B    | C    | B    | A    | A    | B    |
| Data Governance    | B    | B    | B    | B    | B    | A    |

**Legend:** A = Expert, B = Proficient, C = Awareness

---

**End of Standard**
