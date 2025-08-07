# Concept Phase Requirements Folder – File List

Below is the recommended set of artefacts that reside under:

```
A-Q-U-A_V/PRODUCT_LINES/AMPEL360/HYBRID_ELECTRIC/CONCEPT/Robbbo-T/
```

| Filename                                                                                 | Purpose                                                                              |
| ---------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------ |
| [**.gitkeep**](.gitkeep)                                                                 | Preserve directory structure in Git when folder is otherwise empty.                  |
| [**README.md**](README.md)                                                               | Quick orientation to the Concept‑phase package, naming and versioning rules.         |
| [**AQUA-V-AMPEL360-HE-PRD-v6.0.md**](AQUA-V-AMPEL360-HE-PRD-v6.0.md)                     | *Product Requirements Document* – approved v6.0 baseline.                            |
| [**AQUA-V-AMPEL360-HE-SyRS-v1.0.md**](AQUA-V-AMPEL360-HE-SyRS-v1.0.md)                   | *System Requirements Specification* – initial Concept baseline.                      |
| [**AQUA-V-AMPEL360-HE-TRD-v1.0.md**](AQUA-V-AMPEL360-HE-TRD-v1.0.md)                     | *Technical Requirements Document* – subsystem performance targets.                   |
| [**AQUA-V-AMPEL360-HE-IRS-v1.0.md**](AQUA-V-AMPEL360-HE-IRS-v1.0.md)                     | *Interface Requirements Specification* – mechanical, electrical & data interfaces.   |
| [**AQUA-V-AMPEL360-HE-HS-v1.0.md**](AQUA-V-AMPEL360-HE-HS-v1.0.md)                       | *Hazard Specification* – safety & risk mitigation requirements.                      |
| [**AQUA-V-AMPEL360-HE-RAM-v1.0.md**](AQUA-V-AMPEL360-HE-RAM-v1.0.md)                     | *Reliability, Availability & Maintainability Requirements*.                          |
| [**AQUA-V-AMPEL360-HE-ENV-v1.0.md**](AQUA-V-AMPEL360-HE-ENV-v1.0.md)                     | *Environmental & Regulatory Requirements* – EMI/EMC, temperature, vibration.         |
| [**AQUA-V-AMPEL360-HE-VVP-v1.0.md**](AQUA-V-AMPEL360-HE-VVP-v1.0.md)                     | *Verification & Validation Plan* – maps each requirement to its verification method. |
| [**AQUA-V-AMPEL360-HE-ComplianceMatrix.xlsx**](AQUA-V-AMPEL360-HE-ComplianceMatrix.xlsx) | Traceability matrix (auto‑generated).                                                |
| [**CHANGELOG.md**](CHANGELOG.md)                                                         | Chronological log of changes to requirement artefacts.                               |
| [**references/.gitkeep**](references/.gitkeep)                                           | Placeholder for standards, external specs & research papers.                         |

## Versioning Convention

* `<doc>-vMAJOR.MINOR.md` where **MAJOR** denotes a baseline release and **MINOR** denotes incremental edits.
* Increment **MAJOR** only after formal approval.

## Change‑Control Tips

1. Update `CHANGELOG.md` with every commit.
2. Create pull requests for all edits to ensure peer review.
3. Keep auto‑generated artefacts (e.g. compliance matrix) in separate commits to minimise merge noise.

---

*Last updated: 07 Aug 2025 – Europe/Madrid (UTC+02:00)*

