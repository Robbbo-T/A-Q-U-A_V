# Concept Phase Requirements Folder – File List

Below is the recommended set of artefacts that now reside under:

```
A-Q-U-A_V/PRODUCT_LINES/AMPEL360/HYBRID_ELECTRIC/CONCEPT/Robbbo-T/
```

| Filename                                     | Purpose                                                                              | Status           |
| -------------------------------------------- | ------------------------------------------------------------------------------------ | ---------------- |
| **.gitkeep**                                 | Preserve directory structure in Git when folder is otherwise empty.                  | Added            |
| **README.md**                                | Quick orientation to the Concept‑phase package, naming and versioning rules.         | Added            |
| **AQUA-V-AMPEL360-HE-PRD-v6.0.md**           | *Product Requirements Document* – approved v6.0 baseline.                            | Placeholder      |
| **AQUA-V-AMPEL360-HE-SyRS-v1.0.md**          | *System Requirements Specification* – initial Concept baseline.                      | Added (complete) |
| **AQUA-V-AMPEL360-HE-TRD-v1.0.md**           | *Technical Requirements Document* – subsystem performance targets.                   | Placeholder      |
| **AQUA-V-AMPEL360-HE-IRS-v1.0.md**           | *Interface Requirements Specification* – mechanical, electrical & data interfaces.   | Placeholder      |
| **AQUA-V-AMPEL360-HE-HS-v1.0.md**            | *Hazard Specification* – safety & risk mitigation requirements.                      | Placeholder      |
| **AQUA-V-AMPEL360-HE-RAM-v1.0.md**           | *Reliability, Availability & Maintainability Requirements*.                          | Placeholder      |
| **AQUA-V-AMPEL360-HE-ENV-v1.0.md**           | *Environmental & Regulatory Requirements* – EMI/EMC, temperature, vibration.         | Placeholder      |
| **AQUA-V-AMPEL360-HE-VVP-v1.0.md**           | *Verification & Validation Plan* – maps each requirement to its verification method. | Placeholder      |
| **AQUA-V-AMPEL360-HE-ComplianceMatrix.xlsx** | Traceability matrix (auto‑generated).                                                | Added (empty)    |
| **CHANGELOG.md**                             | Chronological log of changes to requirement artefacts.                               | Added            |
| **references/.gitkeep**                      | Placeholder for standards, external specs & research papers.                         | Added            |

## Versioning Convention

* `<doc>-vMAJOR.MINOR.md` where **MAJOR** denotes a baseline release and **MINOR** denotes incremental edits.
* Increment **MAJOR** only after formal approval.

## Change‑Control Tips

1. Update `CHANGELOG.md` with every commit.
2. Create pull requests for all edits to ensure peer review.
3. Keep auto‑generated artefacts (e.g. compliance matrix) in separate commits to minimise merge noise.

---

*Last updated: 07 Aug 2025 – Europe/Madrid (UTC+02:00)*
