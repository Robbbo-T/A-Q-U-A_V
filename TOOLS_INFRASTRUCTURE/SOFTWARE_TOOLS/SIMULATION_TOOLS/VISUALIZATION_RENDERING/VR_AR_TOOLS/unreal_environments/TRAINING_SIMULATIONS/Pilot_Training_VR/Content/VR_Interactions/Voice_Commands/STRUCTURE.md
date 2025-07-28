
```
Voice_Commands/
│
├── AMP-TRAIN-VR001-DES-BOB-R&I-TD-ACV-771-00-01-README-QSTR-v7.6.0.md
├── AMP-TRAIN-VR001-DES-BOB-S&L-TD-CYB-823-00-01-LICENSE-QSTR-v7.6.0.md
├── AMP-TRAIN-VR001-DES-BOB-CDG-SM-CYB-891-00-01-GITIGNORE-QDAT-v7.6.0
├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-324-00-01-PACKAGE-QDAT-v7.6.0.json
├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-325-00-01-CMAKE-QMEC-v7.6.0.txt
│
├── Core/
│   ├── VoiceRecognitionEngine/
│   │   ├── SpeechToText/
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-341-01-01-SPEECHRECOG-QDAT-v7.6.0.cpp
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-341-01-02-SPEECHRECOG-QDAT-v7.6.0.h
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-341-02-01-AUDIOSTREAM-QDAT-v7.6.0.cpp
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-341-02-02-AUDIOSTREAM-QDAT-v7.6.0.h
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-341-03-01-WAVEFORM-QDAT-v7.6.0.cpp
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-341-03-02-WAVEFORM-QDAT-v7.6.0.h
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-341-04-01-LANGMODEL-QDAT-v7.6.0.cpp
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-341-04-02-LANGMODEL-QDAT-v7.6.0.h
│   │   │   └── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-341-05-01-RECOGCONFIG-QDAT-v7.6.0.json
│   │   │
│   │   ├── NaturalLanguageProcessing/
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-342-01-01-NLPENGINE-QDAT-v7.6.0.cpp
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-342-01-02-NLPENGINE-QDAT-v7.6.0.h
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-342-02-01-INTENTCLASS-QDAT-v7.6.0.cpp
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-342-02-02-INTENTCLASS-QDAT-v7.6.0.h
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-342-03-01-ENTITYEXT-QDAT-v7.6.0.cpp
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-342-03-02-ENTITYEXT-QDAT-v7.6.0.h
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-342-04-01-CONTEXTMGR-QDAT-v7.6.0.cpp
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-342-04-02-CONTEXTMGR-QDAT-v7.6.0.h
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-342-05-01-GRAMMAR-QDAT-v7.6.0.xml
│   │   │   └── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-342-06-01-INTENTMAP-QDAT-v7.6.0.json
│   │   │
│   │   ├── CommandParser/
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-343-01-01-CMDPARSER-QDAT-v7.6.0.cpp
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-343-01-02-CMDPARSER-QDAT-v7.6.0.h
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-343-02-01-CMDVALID-QDAT-v7.6.0.cpp
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-343-02-02-CMDVALID-QDAT-v7.6.0.h
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-343-03-01-SYNTAXTREE-QDAT-v7.6.0.cpp
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-343-03-02-SYNTAXTREE-QDAT-v7.6.0.h
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-343-04-01-CMDGRAMMAR-QDAT-v7.6.0.bnf
│   │   │   └── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-343-05-01-PARSERRULES-QDAT-v7.6.0.json
│   │   │
│   │   └── ResponseGenerator/
│   │       ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-344-01-01-RESPENGINE-QDAT-v7.6.0.cpp
│   │       ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-344-01-02-RESPENGINE-QDAT-v7.6.0.h
│   │       ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-344-02-01-TTSINTER-QDAT-v7.6.0.cpp
│   │       ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-344-02-02-TTSINTER-QDAT-v7.6.0.h
│   │       ├── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-344-03-01-RESPTMPL-QDAT-v7.6.0.json
│   │       ├── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-344-04-01-VOICEPROF-QDAT-v7.6.0.dat
│   │       └── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-344-05-01-AUDIOFEED-QDAT-v7.6.0.wav
│   │
│   ├── AudioProcessing/
│   │   ├── NoiseFiltering/
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-345-01-01-NOISEFILTER-QDAT-v7.6.0.cpp
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-345-01-02-NOISEFILTER-QDAT-v7.6.0.h
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-345-02-01-SPECTRSUB-QDAT-v7.6.0.cpp
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-345-02-02-SPECTRSUB-QDAT-v7.6.0.h
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-345-03-01-ADAPTFILT-QDAT-v7.6.0.cpp
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-345-03-02-ADAPTFILT-QDAT-v7.6.0.h
│   │   │   └── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-345-04-01-NOISEPROF-QDAT-v7.6.0.dat
│   │   │
│   │   ├── FeatureExtraction/
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-346-01-01-MFCCEXTRACT-QDAT-v7.6.0.cpp
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-346-01-02-MFCCEXTRACT-QDAT-v7.6.0.h
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-346-02-01-ZEROCROSS-QDAT-v7.6.0.cpp
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-346-02-02-ZEROCROSS-QDAT-v7.6.0.h
│   │   │   └── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-346-03-01-FEATURECFG-QDAT-v7.6.0.json
│   │   │
│   │   └── VoiceActivityDetection/
│   │       ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-347-01-01-VADENGINE-QDAT-v7.6.0.cpp
│   │       ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-347-01-02-VADENGINE-QDAT-v7.6.0.h
│   │       └── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-347-02-01-VADCALIB-QDAT-v7.6.0.json
│   │
│   └── CommandRegistry/
│       ├── CommandDefinitions/
│       │   ├── AMP-TRAIN-VR001-DES-BOB-FUN-TD-ACV-771-01-01-MASTERCMD-QCOM-v7.6.0.json
│       │   ├── AMP-TRAIN-VR001-DES-BOB-FUN-TD-ACV-771-02-01-CMDSCHEMA-QCOM-v7.6.0.xsd
│       │   ├── AMP-TRAIN-VR001-DES-BOB-FUN-TD-ACV-771-03-01-CMDCATEG-QCOM-v7.6.0.json
│       │   ├── AMP-TRAIN-VR001-DES-BOB-FUN-TD-ACV-771-04-01-CMDPRIO-QCOM-v7.6.0.json
│       │   └── AMP-TRAIN-VR001-DES-BOB-FUN-TD-ACV-771-05-01-CMDALIAS-QCOM-v7.6.0.json
│       │
│       ├── RuntimeConfig/
│       │   ├── AMP-TRAIN-VR001-DES-BOB-FUN-TD-ACV-771-06-01-CMDGROUPS-QCOM-v7.6.0.json
│       │   ├── AMP-TRAIN-VR001-DES-BOB-FUN-TD-ACV-771-07-01-CMDSYNONYM-QCOM-v7.6.0.json
│       │   └── AMP-TRAIN-VR001-DES-BOB-FUN-TD-ACV-771-08-01-CMDENABLE-QCOM-v7.6.0.json
│       │
│       └── Log/
│           └── AMP-TRAIN-VR001-DES-BOB-FUN-TD-ACV-771-09-01-CMDHISTORY-QCOM-v7.6.0.log
│
├── CommandCategories/
│   ├── FlightControl/
│   │   ├── BasicManeuvers/
│   │   │   ├── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-ATA-027-01-01-BASICCMD-QAIR-v7.6.0.json
│   │   │   ├── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-ATA-027-02-01-TURNCMD-QAIR-v7.6.0.json
│   │   │   ├── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-ATA-027-03-01-ALTCMD-QAIR-v7.6.0.json
│   │   │   ├── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-ATA-027-04-01-SPEEDCMD-QAIR-v7.6.0.json
│   │   │   ├── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-ATA-027-05-01-HDGCMD-QAIR-v7.6.0.json
│   │   │   └── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-ATA-027-06-01-ATTCMD-QAIR-v7.6.0.json
│   │   │
│   │   ├── AdvancedManeuvers/
│   │   │   ├── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-ATA-027-07-01-AUTOLAND-QAIR-v7.6.0.json
│   │   │   ├── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-ATA-027-08-01-APPROACH-QAIR-v7.6.0.json
│   │   │   └── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-ATA-027-09-01-TAKEOFF-QAIR-v7.6.0.json
│   │   │
│   │   └── EmergencyProcedures/
│   │       ├── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-ATA-027-10-01-EMERGDESC-QAIR-v7.6.0.json
│   │       └── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-ATA-027-11-01-EMERGLIST-QAIR-v7.6.0.json
│   │
│   ├── SystemsManagement/
│   │   ├── QuantumSystems/
│   │   │   ├── QNS_Commands/
│   │   │   │   ├── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-QCSAA-934-01-01-QNSACT-QSCI-v7.6.0.json
│   │   │   │   ├── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-QCSAA-934-02-01-QNSCAL-QSCI-v7.6.0.json
│   │   │   │   ├── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-QCSAA-934-03-01-QNSNAV-QSCI-v7.6.0.json
│   │   │   │   ├── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-QCSAA-934-04-01-QNSFAIL-QSCI-v7.6.0.json
│   │   │   │   └── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-QCSAA-934-05-01-QNSDIAG-QSCI-v7.6.0.json
│   │   │   │
│   │   │   ├── QPU_Commands/
│   │   │   │   ├── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-QCSAA-935-01-01-QPUINIT-QSCI-v7.6.0.json
│   │   │   │   ├── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-QCSAA-935-02-01-QPUEXEC-QSCI-v7.6.0.json
│   │   │   │   └── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-QCSAA-935-03-01-QPUSTAT-QSCI-v7.6.0.json
│   │   │   │
│   │   │   └── QDS_Commands/
│   │   │       ├── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-QCSAA-936-01-01-QDSINIT-QSCI-v7.6.0.json
│   │   │       ├── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-QCSAA-936-02-01-QDSREAD-QSCI-v7.6.0.json
│   │   │       └── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-QCSAA-936-03-01-QDSHIST-QSCI-v7.6.0.json
│   │   │
│   │   └── EnvironmentalControl/
│   │       ├── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-ATA-021-01-01-TEMPSET-QMEC-v7.6.0.json
│   │       └── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-ATA-021-02-01-PRESSET-QMEC-v7.6.0.json
│   │
│   └── Communications/
│       ├── ExternalComms/
│       │   ├── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-ATA-023-01-01-RADIOSET-QCOM-v7.6.0.json
│       │   └── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-ATA-023-02-01-SATCOMS-QCOM-v7.6.0.json
│       │
│       └── InternalComms/
│           ├── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-ATA-023-03-01-INTERCOM-QCOM-v7.6.0.json
│           └── AMP-TRAIN-VR001-OPS-BOB-FUN-TD-ATA-023-04-01-PAANNOUNCE-QCOM-v7.6.0.json
│
├── TrainingScenarios/
│   ├── BasicTraining/
│   │   ├── VoiceCommandIntro/
│   │   │   ├── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-ACV-778-01-01-LESSON01-QHPC-v7.6.0.scenario
│   │   │   ├── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-ACV-778-02-01-LESSON02-QHPC-v7.6.0.scenario
│   │   │   ├── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-ACV-778-03-01-LESSON03-QHPC-v7.6.0.scenario
│   │   │   ├── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-ACV-778-04-01-LESSON04-QHPC-v7.6.0.scenario
│   │   │   └── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-ACV-778-05-01-LESSON05-QHPC-v7.6.0.scenario
│   │   │
│   │   ├── BasicFlightOps/
│   │   │   ├── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-ACV-778-06-01-TAKEOFFSC-QHPC-v7.6.0.scenario
│   │   │   ├── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-ACV-778-07-01-LANDINGSC-QHPC-v7.6.0.scenario
│   │   │   └── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-ACV-778-08-01-CRUISESC-QHPC-v7.6.0.scenario
│   │   │
│   │   └── EmergencyProcedures/
│   │       ├── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-ACV-778-09-01-ENGFAILSC-QHPC-v7.6.0.scenario
│   │       └── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-ACV-778-10-01-HYDFAILSC-QHPC-v7.6.0.scenario
│   │
│   ├── QuantumSystemsTraining/
│   │   ├── QNS_Operations/
│   │   │   ├── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-QCSAA-941-01-01-QNSBASIC-QSCI-v7.6.0.scenario
│   │   │   ├── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-QCSAA-941-02-01-QNSGPSDEN-QSCI-v7.6.0.scenario
│   │   │   ├── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-QCSAA-941-03-01-QNSCALIB-QSCI-v7.6.0.scenario
│   │   │   └── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-QCSAA-941-04-01-QNSINTEG-QSCI-v7.6.0.scenario
│   │   │
│   │   ├── QPU_Interaction/
│   │   │   ├── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-QCSAA-942-01-01-QPUBASIC-QSCI-v7.6.0.scenario
│   │   │   ├── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-QCSAA-942-02-01-QPUDEBUG-QSCI-v7.6.0.scenario
│   │   │   └── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-QCSAA-942-03-01-QPUOPTIM-QSCI-v7.6.0.scenario
│   │   │
│   │   └── QDS_Diagnostics/
│   │       ├── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-QCSAA-943-01-01-QDSHEALTH-QSCI-v7.6.0.scenario
│   │       └── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-QCSAA-943-02-01-QDSFAULT-QSCI-v7.6.0.scenario
│   │
│   └── AdvancedScenarios/
│       ├── ComplexNavigation/
│       │   ├── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-ATA-034-01-01-HIGHALT-QAIR-v7.6.0.scenario
│       │   └── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-ATA-034-02-01-SUBORBIT-QSPA-v7.6.0.scenario
│       │
│       └── MultiAircraftCoordination/
│           ├── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-ACV-702-01-01-ATCCOMM-QCOM-v7.6.0.scenario
│           └── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-ACV-702-02-01-SWARMCTL-QCOM-v7.6.0.scenario
│
├── Integration/
│   ├── UnrealEnginePlugins/
│   │   ├── VoiceCommandPlugin/
│   │   │   ├── Source/
│   │   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-351-01-01-VCPLUGIN-QHPC-v7.6.0.cpp
│   │   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-351-01-02-VCPLUGIN-QHPC-v7.6.0.h
│   │   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-351-02-01-VCACTOR-QHPC-v7.6.0.cpp
│   │   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-351-02-02-VCACTOR-QHPC-v7.6.0.h
│   │   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-351-03-01-VCCOMP-QHPC-v7.6.0.cpp
│   │   │   │   └── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-351-03-02-VCCOMP-QHPC-v7.6.0.h
│   │   │   │
│   │   │   ├── Content/
│   │   │   │   ├── Blueprints/
│   │   │   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-DT-DTCEC-352-01-01-VCMGR-QHPC-v7.6.0.uasset
│   │   │   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-DT-DTCEC-352-02-01-VCIND-QHPC-v7.6.0.uasset
│   │   │   │   │   └── AMP-TRAIN-VR001-DES-BOB-TEC-DT-DTCEC-352-03-01-CMDFB-QHPC-v7.6.0.uasset
│   │   │   │   │
│   │   │   │   └── Materials/
│   │   │   │       ├── AMP-TRAIN-VR001-DES-BOB-TEC-DT-DTCEC-353-01-01-VCACT-QHPC-v7.6.0.uasset
│   │   │   │       └── AMP-TRAIN-VR001-DES-BOB-TEC-DT-DTCEC-353-02-01-VCINACT-QHPC-v7.6.0.uasset
│   │   │   │
│   │   │   └── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-354-01-01-VCPLUGIN-QHPC-v7.6.0.uplugin
│   │   │
│   │   └── SimulatorIntegration/
│   │       ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-355-01-01-SIMIF-QHPC-v7.6.0.cpp
│   │       ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-355-01-02-SIMIF-QHPC-v7.6.0.h
│   │       └── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-355-02-01-SIMCFG-QHPC-v7.6.0.json
│   │
│   └── APIIntegration/
│       ├── ExternalAPIs/
│       │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-356-01-01-WEATHERAPI-QCOM-v7.6.0.cpp
│       │   └── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-356-02-01-TRAFFICAPI-QCOM-v7.6.0.cpp
│       │
│       └── InternalAPIs/
│           ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-357-01-01-AVIONICSAPI-QMEC-v7.6.0.cpp
│           └── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-357-02-01-ENGINESAPI-QPOW-v7.6.0.cpp
│
├── Testing/
│   ├── UnitTests/
│   │   ├── CommandRecognition/
│   │   │   ├── AMP-TRAIN-VR001-VAL-BOB-TEC-SM-CYB-871-01-01-TESTSPEECH-QDAT-v7.6.0.py
│   │   │   ├── AMP-TRAIN-VR001-VAL-BOB-TEC-SM-CYB-871-02-01-TESTNLP-QDAT-v7.6.0.py
│   │   │   ├── AMP-TRAIN-VR001-VAL-BOB-TEC-SM-CYB-871-03-01-TESTPARSE-QDAT-v7.6.0.py
│   │   │   ├── AMP-TRAIN-VR001-VAL-BOB-TEC-SM-CYB-871-04-01-TESTINTENT-QDAT-v7.6.0.py
│   │   │   └── AMP-TRAIN-VR001-VAL-BOB-TEC-TD-CYB-871-05-01-FIXTURES-QDAT-v7.6.0.json
│   │   │
│   │   ├── AudioProcessingTests/
│   │   │   ├── AMP-TRAIN-VR001-VAL-BOB-TEC-SM-DTCEC-345-05-01-TESTNOISE-QDAT-v7.6.0.py
│   │   │   ├── AMP-TRAIN-VR001-VAL-BOB-TEC-SM-DTCEC-346-04-01-TESTFEATEXT-QDAT-v7.6.0.py
│   │   │   └── AMP-TRAIN-VR001-VAL-BOB-TEC-SM-DTCEC-347-03-01-TESTVAD-QDAT-v7.6.0.py
│   │   │
│   │   └── IntegrationTests/
│   │       ├── AMP-TRAIN-VR001-VAL-BOB-TEC-SM-DTCEC-351-04-01-TESTPLUGIN-QHPC-v7.6.0.py
│   │       └── AMP-TRAIN-VR001-VAL-BOB-TEC-SM-DTCEC-355-03-01-TESTSIMIF-QHPC-v7.6.0.py
│   │
│   └── ValidationReports/
│       ├── EASACompliance/
│       │   ├── AMP-TRAIN-VR001-CER-BOB-REG-TD-ATA-025-01-01-CS25VOICE-QGRO-v7.6.0.pdf
│       │   ├── AMP-TRAIN-VR001-CER-BOB-REG-TD-ATA-025-02-01-SCVTOLREQ-QGRO-v7.6.0.pdf
│       │   ├── AMP-TRAIN-VR001-CER-BOB-REG-TD-ATA-025-03-01-TESTEVID-QGRO-v7.6.0.zip
│       │   └── AMP-TRAIN-VR001-CER-BOB-REG-TD-ATA-025-04-01-CERTCHECK-QGRO-v7.6.0.xlsx
│       │
│       ├── FAACompliance/
│       │   ├── AMP-TRAIN-VR001-CER-BOB-REG-TD-ATA-025-05-01-FAACOMPL-QGRO-v7.6.0.pdf
│       │   └── AMP-TRAIN-VR001-CER-BOB-REG-TD-ATA-025-06-01-TESTDATA-QGRO-v7.6.0.zip
│       │
│       └── PerformanceReports/
│           ├── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-DTCEC-341-06-01-STTACC-QDAT-v7.6.0.pdf
│           ├── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-DTCEC-342-07-01-NLPUND-QDAT-v7.6.0.pdf
│           ├── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-DTCEC-343-06-01-CMDRELIAB-QDAT-v7.6.0.pdf
│           └── AMP-TRAIN-VR001-VAL-BOB-R&I-TD-DTCEC-344-06-01-RESPGENQUAL-QDAT-v7.6.0.pdf
│
├── Documentation/
│   ├── DeveloperGuides/
│   │   ├── APIReference/
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-381-01-01-VOICEAPI-QDAT-v7.6.0.md
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-381-02-01-CMDAPI-QDAT-v7.6.0.md
│   │   │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-381-03-01-INTEGAPI-QDAT-v7.6.0.md
│   │   │   └── Examples/
│   │   │       ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-382-01-01-BASICINT-QDAT-v7.6.0.cpp
│   │   │       ├── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-382-02-01-ADVFEAT-QDAT-v7.6.0.cpp
│   │   │       └── AMP-TRAIN-VR001-DES-BOB-TEC-SM-DTCEC-382-03-01-CUSTCMD-QDAT-v7.6.0.cpp
│   │   │
│   │   └── IntegrationGuide/
│   │       ├── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-383-01-01-UEINTEG-QHPC-v7.6.0.md
│   │       └── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-383-02-01-SIMINTEG-QHPC-v7.6.0.md
│   │
│   └── UserManuals/
│       ├── AMP-TRAIN-VR001-DES-BOB-CES-TD-ATA-000-01-01-USRMANUAL-QGRO-v7.6.0.pdf
│       └── AMP-TRAIN-VR001-DES-BOB-CES-TD-ATA-000-02-01-QRHVOICE-QGRO-v7.6.0.pdf
│
└── Config/
    ├── SystemSettings/
    │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-391-01-01-AUDIOSET-QDAT-v7.6.0.config
    │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-391-02-01-RECOGTHRESH-QDAT-v7.6.0.config
    │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-391-03-01-LANGMODELS-QDAT-v7.6.0.config
    │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-391-04-01-SYSPARAM-QDAT-v7.6.0.config
    │   ├── AMP-TRAIN-VR001-DES-BOB-TEC-TD-DTCEC-391-05-01-NETSET-QDAT-v7.6.0.config
    │   └── AMP-TRAIN-VR001-DES-BOB-CDG-TD-CYB-892-01-01-SECSET-QDAT-v7.6.0.config
    │
    └── DeploymentSettings/
        ├── AMP-TRAIN-VR001-DES-BOB-ORG-TD-DTCEC-392-01-01-DEPLCONF-QDAT-v7.6.0.json
        └── AMP-TRAIN-VR001-DES-BOB-ORG-TD-DTCEC-392-02-01-ENVCONF-QDAT-v7.6.0.env

```

Key aspects of the AQUA V. nomenclature applied:

1. **Product Line**: `AMP` (AMPEL360) since this is pilot training
2. **Product**: `TRAIN-VR001` (Training VR System 001)
3. **MSN**: Various serial numbers for different components
4. **Phase**: `DES` (Design), `OPS` (Operations), `VAL` (Validation), `CER` (Certification)
5. **ALI/BOB**: All `BOB` (digital/virtual system)
6. **Artifact Categories**: `TEC`, `FUN`, `R&I`, `REG`, `CDG`, etc.
7. **Document Types**: `SM` (Software Module), `TD` (Technical Document), `DT` (Digital Twin)
8. **UTCS Codes**: Various from the 1,000 chapters
9. **Q-Division**: `QDAT`, `QHPC`, `QCOM`, `QSCI`, `QAIR`, `QGRO`
10. **Version**: All `v7.6.0` to match current system version

This structure now properly follows the AQUA V. documentation standards!
