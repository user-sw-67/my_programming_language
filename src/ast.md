```mermaid
%%{init: { 'theme': 'base', 'themeVariables': { 'primaryColor': '#ffffff', 'primaryTextColor': '#000000', 'lineColor': '#333333' }, 'graph': {'rankSep': 120, 'nodeSep': 100}} }%%
graph TD
  classDef root_style fill:#222,color:#fff,stroke:#000,stroke-width:4px;
  classDef var_style fill:#bbdefb,color:#000,stroke:#1565c0,stroke-width:2px;
  classDef op_style fill:#f3e5f5,color:#000,stroke:#7b1fa2,stroke-width:2px;
  classDef logic_style fill:#fff9c4,color:#000,stroke:#fbc02d,stroke-width:2px;
  classDef func_style fill:#c8e6c9,color:#000,stroke:#2e7d32,stroke-width:2px;
  classDef test_style fill:#ffe0b2,color:#000,stroke:#fb8c00,stroke-width:2px;
  classDef assert_style fill:#ffcdd2,color:#000,stroke:#e53935,stroke-width:2px;
  node_0(("   🚀 КОРЕНЬ ПРОГРАММЫ   " ))
  class node_0 root_style
  node_1[["   🏛️ КЛАСС: Task   " ]]
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_1
  class node_1 root_style
  node_2(["    private ПОЛЕ   " ])
  node_1 -- " <font color='black'><b>член_класса</b></font> " ----> node_2
  class node_2 var_style
  node_3{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_2 -- " <font color='black'><b>далее</b></font> " ----> node_3
  class node_3 var_style
  node_4(["   ИМЯ: id
Тип: auto   " ])
  node_3 -- " <font color='black'><b>память</b></font> " ----> node_4
  node_5(["    public ПОЛЕ   " ])
  node_1 -- " <font color='black'><b>член_класса</b></font> " ----> node_5
  class node_5 var_style
  node_6{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_5 -- " <font color='black'><b>далее</b></font> " ----> node_6
  class node_6 var_style
  node_7(["   ИМЯ: title
Тип: auto   " ])
  node_6 -- " <font color='black'><b>память</b></font> " ----> node_7
  node_8(["    public ПОЛЕ   " ])
  node_1 -- " <font color='black'><b>член_класса</b></font> " ----> node_8
  class node_8 var_style
  node_9{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_8 -- " <font color='black'><b>далее</b></font> " ----> node_9
  class node_9 var_style
  node_10(["   ИМЯ: description
Тип: auto   " ])
  node_9 -- " <font color='black'><b>память</b></font> " ----> node_10
  node_11(["    public ПОЛЕ   " ])
  node_1 -- " <font color='black'><b>член_класса</b></font> " ----> node_11
  class node_11 var_style
  node_12{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_11 -- " <font color='black'><b>далее</b></font> " ----> node_12
  class node_12 var_style
  node_13(["   ИМЯ: completed
Тип: auto   " ])
  node_12 -- " <font color='black'><b>память</b></font> " ----> node_13
  node_14(["    public ПОЛЕ   " ])
  node_1 -- " <font color='black'><b>член_класса</b></font> " ----> node_14
  class node_14 var_style
  node_15{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_14 -- " <font color='black'><b>далее</b></font> " ----> node_15
  class node_15 var_style
  node_16(["   ИМЯ: priority
Тип: auto   " ])
  node_15 -- " <font color='black'><b>память</b></font> " ----> node_16
  node_17(["    public ПОЛЕ   " ])
  node_1 -- " <font color='black'><b>член_класса</b></font> " ----> node_17
  class node_17 var_style
  node_18{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_17 -- " <font color='black'><b>далее</b></font> " ----> node_18
  class node_18 var_style
  node_19(["   ИМЯ: createdAt
Тип: auto   " ])
  node_18 -- " <font color='black'><b>память</b></font> " ----> node_19
  node_20(("    public МЕТОД: new   " ))
  node_1 -- " <font color='black'><b>член_класса</b></font> " ----> node_20
  class node_20 func_style
  node_21(("   🔨 ФУНКЦИЯ: new
Вернет: auto   " ))
  node_20 -- " <font color='black'><b>далее</b></font> " ----> node_21
  class node_21 func_style
  node_22(["   АРГ: id (auto)   " ])
  node_21 -- " <font color='black'><b>сигнатура</b></font> " ----> node_22
  node_23(["   АРГ: title (auto)   " ])
  node_21 -- " <font color='black'><b>сигнатура</b></font> " ----> node_23
  node_24(["   АРГ: description (auto)   " ])
  node_21 -- " <font color='black'><b>сигнатура</b></font> " ----> node_24
  node_25(["   АРГ: priority (auto)   " ])
  node_21 -- " <font color='black'><b>сигнатура</b></font> " ----> node_25
  node_26["   📂 БЛОК КОДА { }   " ]
  node_21 -- " <font color='black'><b>далее</b></font> " ----> node_26
  node_27["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_26 -- " <font color='black'><b>далее</b></font> " ----> node_27
  class node_27 op_style
  node_28["   ⚙️ ОПЕРАЦИЯ    " ]
  node_27 -- " <font color='black'><b>далее</b></font> " ----> node_28
  class node_28 op_style
  node_29(["   🔍 this   " ])
  node_28 -- " <font color='black'><b>далее</b></font> " ----> node_29
  node_30(["   🔍 id   " ])
  node_28 -- " <font color='black'><b>далее</b></font> " ----> node_30
  node_31(["   🔍 id   " ])
  node_27 -- " <font color='black'><b>далее</b></font> " ----> node_31
  node_32["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_26 -- " <font color='black'><b>далее</b></font> " ----> node_32
  class node_32 op_style
  node_33["   ⚙️ ОПЕРАЦИЯ    " ]
  node_32 -- " <font color='black'><b>далее</b></font> " ----> node_33
  class node_33 op_style
  node_34(["   🔍 this   " ])
  node_33 -- " <font color='black'><b>далее</b></font> " ----> node_34
  node_35(["   🔍 title   " ])
  node_33 -- " <font color='black'><b>далее</b></font> " ----> node_35
  node_36(["   🔍 title   " ])
  node_32 -- " <font color='black'><b>далее</b></font> " ----> node_36
  node_37["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_26 -- " <font color='black'><b>далее</b></font> " ----> node_37
  class node_37 op_style
  node_38["   ⚙️ ОПЕРАЦИЯ    " ]
  node_37 -- " <font color='black'><b>далее</b></font> " ----> node_38
  class node_38 op_style
  node_39(["   🔍 this   " ])
  node_38 -- " <font color='black'><b>далее</b></font> " ----> node_39
  node_40(["   🔍 description   " ])
  node_38 -- " <font color='black'><b>далее</b></font> " ----> node_40
  node_41(["   🔍 description   " ])
  node_37 -- " <font color='black'><b>далее</b></font> " ----> node_41
  node_42["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_26 -- " <font color='black'><b>далее</b></font> " ----> node_42
  class node_42 op_style
  node_43["   ⚙️ ОПЕРАЦИЯ    " ]
  node_42 -- " <font color='black'><b>далее</b></font> " ----> node_43
  class node_43 op_style
  node_44(["   🔍 this   " ])
  node_43 -- " <font color='black'><b>далее</b></font> " ----> node_44
  node_45(["   🔍 priority   " ])
  node_43 -- " <font color='black'><b>далее</b></font> " ----> node_45
  node_46(["   🔍 priority   " ])
  node_42 -- " <font color='black'><b>далее</b></font> " ----> node_46
  node_47["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_26 -- " <font color='black'><b>далее</b></font> " ----> node_47
  class node_47 op_style
  node_48["   ⚙️ ОПЕРАЦИЯ    " ]
  node_47 -- " <font color='black'><b>далее</b></font> " ----> node_48
  class node_48 op_style
  node_49(["   🔍 this   " ])
  node_48 -- " <font color='black'><b>далее</b></font> " ----> node_49
  node_50(["   🔍 completed   " ])
  node_48 -- " <font color='black'><b>далее</b></font> " ----> node_50
  node_51["   💎 false   "]
  node_47 -- " <font color='black'><b>далее</b></font> " ----> node_51
  node_52["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_26 -- " <font color='black'><b>далее</b></font> " ----> node_52
  class node_52 op_style
  node_53["   ⚙️ ОПЕРАЦИЯ    " ]
  node_52 -- " <font color='black'><b>далее</b></font> " ----> node_53
  class node_53 op_style
  node_54(["   🔍 this   " ])
  node_53 -- " <font color='black'><b>далее</b></font> " ----> node_54
  node_55(["   🔍 createdAt   " ])
  node_53 -- " <font color='black'><b>далее</b></font> " ----> node_55
  node_56(["   🚀 ВЫЗОВ: getCurrentTime()   " ])
  node_52 -- " <font color='black'><b>далее</b></font> " ----> node_56
  class node_56 func_style
  node_57(("    public МЕТОД: id «get»   " ))
  node_1 -- " <font color='black'><b>член_класса</b></font> " ----> node_57
  class node_57 func_style
  node_58(("   🔨 ФУНКЦИЯ: id
Вернет: auto   " ))
  node_57 -- " <font color='black'><b>далее</b></font> " ----> node_58
  class node_58 func_style
  node_59["   📂 БЛОК КОДА { }   " ]
  node_58 -- " <font color='black'><b>далее</b></font> " ----> node_59
  node_60[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_59 -- " <font color='black'><b>далее</b></font> " ----> node_60
  node_61["   ⚙️ ОПЕРАЦИЯ    " ]
  node_60 -- " <font color='black'><b>далее</b></font> " ----> node_61
  class node_61 op_style
  node_62(["   🔍 this   " ])
  node_61 -- " <font color='black'><b>далее</b></font> " ----> node_62
  node_63(["   🔍 id   " ])
  node_61 -- " <font color='black'><b>далее</b></font> " ----> node_63
  node_64(("    public МЕТОД: title «get»   " ))
  node_1 -- " <font color='black'><b>член_класса</b></font> " ----> node_64
  class node_64 func_style
  node_65(("   🔨 ФУНКЦИЯ: title
Вернет: auto   " ))
  node_64 -- " <font color='black'><b>далее</b></font> " ----> node_65
  class node_65 func_style
  node_66["   📂 БЛОК КОДА { }   " ]
  node_65 -- " <font color='black'><b>далее</b></font> " ----> node_66
  node_67[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_66 -- " <font color='black'><b>далее</b></font> " ----> node_67
  node_68["   ⚙️ ОПЕРАЦИЯ    " ]
  node_67 -- " <font color='black'><b>далее</b></font> " ----> node_68
  class node_68 op_style
  node_69(["   🔍 this   " ])
  node_68 -- " <font color='black'><b>далее</b></font> " ----> node_69
  node_70(["   🔍 title   " ])
  node_68 -- " <font color='black'><b>далее</b></font> " ----> node_70
  node_71(("    public МЕТОД: description «get»   " ))
  node_1 -- " <font color='black'><b>член_класса</b></font> " ----> node_71
  class node_71 func_style
  node_72(("   🔨 ФУНКЦИЯ: description
Вернет: auto   " ))
  node_71 -- " <font color='black'><b>далее</b></font> " ----> node_72
  class node_72 func_style
  node_73["   📂 БЛОК КОДА { }   " ]
  node_72 -- " <font color='black'><b>далее</b></font> " ----> node_73
  node_74[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_73 -- " <font color='black'><b>далее</b></font> " ----> node_74
  node_75["   ⚙️ ОПЕРАЦИЯ    " ]
  node_74 -- " <font color='black'><b>далее</b></font> " ----> node_75
  class node_75 op_style
  node_76(["   🔍 this   " ])
  node_75 -- " <font color='black'><b>далее</b></font> " ----> node_76
  node_77(["   🔍 description   " ])
  node_75 -- " <font color='black'><b>далее</b></font> " ----> node_77
  node_78(("    public МЕТОД: completed «get»   " ))
  node_1 -- " <font color='black'><b>член_класса</b></font> " ----> node_78
  class node_78 func_style
  node_79(("   🔨 ФУНКЦИЯ: completed
Вернет: auto   " ))
  node_78 -- " <font color='black'><b>далее</b></font> " ----> node_79
  class node_79 func_style
  node_80["   📂 БЛОК КОДА { }   " ]
  node_79 -- " <font color='black'><b>далее</b></font> " ----> node_80
  node_81[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_80 -- " <font color='black'><b>далее</b></font> " ----> node_81
  node_82["   ⚙️ ОПЕРАЦИЯ    " ]
  node_81 -- " <font color='black'><b>далее</b></font> " ----> node_82
  class node_82 op_style
  node_83(["   🔍 this   " ])
  node_82 -- " <font color='black'><b>далее</b></font> " ----> node_83
  node_84(["   🔍 completed   " ])
  node_82 -- " <font color='black'><b>далее</b></font> " ----> node_84
  node_85(("    public МЕТОД: priority «get»   " ))
  node_1 -- " <font color='black'><b>член_класса</b></font> " ----> node_85
  class node_85 func_style
  node_86(("   🔨 ФУНКЦИЯ: priority
Вернет: auto   " ))
  node_85 -- " <font color='black'><b>далее</b></font> " ----> node_86
  class node_86 func_style
  node_87["   📂 БЛОК КОДА { }   " ]
  node_86 -- " <font color='black'><b>далее</b></font> " ----> node_87
  node_88[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_87 -- " <font color='black'><b>далее</b></font> " ----> node_88
  node_89["   ⚙️ ОПЕРАЦИЯ    " ]
  node_88 -- " <font color='black'><b>далее</b></font> " ----> node_89
  class node_89 op_style
  node_90(["   🔍 this   " ])
  node_89 -- " <font color='black'><b>далее</b></font> " ----> node_90
  node_91(["   🔍 priority   " ])
  node_89 -- " <font color='black'><b>далее</b></font> " ----> node_91
  node_92(("    public МЕТОД: createdAt «get»   " ))
  node_1 -- " <font color='black'><b>член_класса</b></font> " ----> node_92
  class node_92 func_style
  node_93(("   🔨 ФУНКЦИЯ: createdAt
Вернет: auto   " ))
  node_92 -- " <font color='black'><b>далее</b></font> " ----> node_93
  class node_93 func_style
  node_94["   📂 БЛОК КОДА { }   " ]
  node_93 -- " <font color='black'><b>далее</b></font> " ----> node_94
  node_95[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_94 -- " <font color='black'><b>далее</b></font> " ----> node_95
  node_96["   ⚙️ ОПЕРАЦИЯ    " ]
  node_95 -- " <font color='black'><b>далее</b></font> " ----> node_96
  class node_96 op_style
  node_97(["   🔍 this   " ])
  node_96 -- " <font color='black'><b>далее</b></font> " ----> node_97
  node_98(["   🔍 createdAt   " ])
  node_96 -- " <font color='black'><b>далее</b></font> " ----> node_98
  node_99(("    public МЕТОД: markComplete   " ))
  node_1 -- " <font color='black'><b>член_класса</b></font> " ----> node_99
  class node_99 func_style
  node_100(("   🔨 ФУНКЦИЯ: markComplete
Вернет: auto   " ))
  node_99 -- " <font color='black'><b>далее</b></font> " ----> node_100
  class node_100 func_style
  node_101["   📂 БЛОК КОДА { }   " ]
  node_100 -- " <font color='black'><b>далее</b></font> " ----> node_101
  node_102["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_101 -- " <font color='black'><b>далее</b></font> " ----> node_102
  class node_102 op_style
  node_103["   ⚙️ ОПЕРАЦИЯ    " ]
  node_102 -- " <font color='black'><b>далее</b></font> " ----> node_103
  class node_103 op_style
  node_104(["   🔍 this   " ])
  node_103 -- " <font color='black'><b>далее</b></font> " ----> node_104
  node_105(["   🔍 completed   " ])
  node_103 -- " <font color='black'><b>далее</b></font> " ----> node_105
  node_106["   💎 true   "]
  node_102 -- " <font color='black'><b>далее</b></font> " ----> node_106
  node_107(("    public МЕТОД: markIncomplete   " ))
  node_1 -- " <font color='black'><b>член_класса</b></font> " ----> node_107
  class node_107 func_style
  node_108(("   🔨 ФУНКЦИЯ: markIncomplete
Вернет: auto   " ))
  node_107 -- " <font color='black'><b>далее</b></font> " ----> node_108
  class node_108 func_style
  node_109["   📂 БЛОК КОДА { }   " ]
  node_108 -- " <font color='black'><b>далее</b></font> " ----> node_109
  node_110["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_109 -- " <font color='black'><b>далее</b></font> " ----> node_110
  class node_110 op_style
  node_111["   ⚙️ ОПЕРАЦИЯ    " ]
  node_110 -- " <font color='black'><b>далее</b></font> " ----> node_111
  class node_111 op_style
  node_112(["   🔍 this   " ])
  node_111 -- " <font color='black'><b>далее</b></font> " ----> node_112
  node_113(["   🔍 completed   " ])
  node_111 -- " <font color='black'><b>далее</b></font> " ----> node_113
  node_114["   💎 false   "]
  node_110 -- " <font color='black'><b>далее</b></font> " ----> node_114
  node_115(("    public МЕТОД: setPriority   " ))
  node_1 -- " <font color='black'><b>член_класса</b></font> " ----> node_115
  class node_115 func_style
  node_116(("   🔨 ФУНКЦИЯ: setPriority
Вернет: auto   " ))
  node_115 -- " <font color='black'><b>далее</b></font> " ----> node_116
  class node_116 func_style
  node_117(["   АРГ: newPriority (auto)   " ])
  node_116 -- " <font color='black'><b>сигнатура</b></font> " ----> node_117
  node_118["   📂 БЛОК КОДА { }   " ]
  node_116 -- " <font color='black'><b>далее</b></font> " ----> node_118
  node_119["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_118 -- " <font color='black'><b>далее</b></font> " ----> node_119
  class node_119 op_style
  node_120["   ⚙️ ОПЕРАЦИЯ    " ]
  node_119 -- " <font color='black'><b>далее</b></font> " ----> node_120
  class node_120 op_style
  node_121(["   🔍 this   " ])
  node_120 -- " <font color='black'><b>далее</b></font> " ----> node_121
  node_122(["   🔍 priority   " ])
  node_120 -- " <font color='black'><b>далее</b></font> " ----> node_122
  node_123(["   🔍 newPriority   " ])
  node_119 -- " <font color='black'><b>далее</b></font> " ----> node_123
  node_124(("    public МЕТОД: toString   " ))
  node_1 -- " <font color='black'><b>член_класса</b></font> " ----> node_124
  class node_124 func_style
  node_125(("   🔨 ФУНКЦИЯ: toString
Вернет: auto   " ))
  node_124 -- " <font color='black'><b>далее</b></font> " ----> node_125
  class node_125 func_style
  node_126["   📂 БЛОК КОДА { }   " ]
  node_125 -- " <font color='black'><b>далее</b></font> " ----> node_126
  node_127{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_126 -- " <font color='black'><b>далее</b></font> " ----> node_127
  class node_127 var_style
  node_128(["   ИМЯ: status
Тип: auto   " ])
  node_127 -- " <font color='black'><b>память</b></font> " ----> node_128
  node_129{"   ⚖️ ТЕРНАРКА (?:)   " }
  node_128 -- " <font color='black'><b>далее</b></font> " ----> node_129
  class node_129 logic_style
  node_130["   ⚙️ ОПЕРАЦИЯ    " ]
  node_129 -- " <font color='black'><b>далее</b></font> " ----> node_130
  class node_130 op_style
  node_131(["   🔍 this   " ])
  node_130 -- " <font color='black'><b>далее</b></font> " ----> node_131
  node_132(["   🔍 completed   " ])
  node_130 -- " <font color='black'><b>далее</b></font> " ----> node_132
  node_133["   💎 Done   "]
  node_129 -- " <font color='black'><b>далее</b></font> " ----> node_133
  node_134["   💎 Pending   "]
  node_129 -- " <font color='black'><b>далее</b></font> " ----> node_134
  node_135{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_126 -- " <font color='black'><b>далее</b></font> " ----> node_135
  class node_135 var_style
  node_136(["   ИМЯ: priorityStr
Тип: auto   " ])
  node_135 -- " <font color='black'><b>память</b></font> " ----> node_136
  node_137["   💎 undefined   "]
  node_136 -- " <font color='black'><b>далее</b></font> " ----> node_137
  node_138{"   ❓ ЕСЛИ (if)   " }
  node_126 -- " <font color='black'><b>далее</b></font> " ----> node_138
  class node_138 logic_style
  node_139["   ⚖️ РАВНО (==)    " ]
  node_138 -- " <font color='black'><b>далее</b></font> " ----> node_139
  class node_139 op_style
  node_140["   ⚙️ ОПЕРАЦИЯ    " ]
  node_139 -- " <font color='black'><b>далее</b></font> " ----> node_140
  class node_140 op_style
  node_141(["   🔍 this   " ])
  node_140 -- " <font color='black'><b>далее</b></font> " ----> node_141
  node_142(["   🔍 priority   " ])
  node_140 -- " <font color='black'><b>далее</b></font> " ----> node_142
  node_143["   💎 1   "]
  node_139 -- " <font color='black'><b>далее</b></font> " ----> node_143
  node_144["   📂 БЛОК КОДА { }   " ]
  node_138 -- " <font color='black'><b>далее</b></font> " ----> node_144
  node_145["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_144 -- " <font color='black'><b>далее</b></font> " ----> node_145
  class node_145 op_style
  node_146(["   🔍 priorityStr   " ])
  node_145 -- " <font color='black'><b>далее</b></font> " ----> node_146
  node_147["   💎 High   "]
  node_145 -- " <font color='black'><b>далее</b></font> " ----> node_147
  node_148{"   ❓ ЕСЛИ (if)   " }
  node_138 -- " <font color='black'><b>далее</b></font> " ----> node_148
  class node_148 logic_style
  node_149["   ⚖️ РАВНО (==)    " ]
  node_148 -- " <font color='black'><b>далее</b></font> " ----> node_149
  class node_149 op_style
  node_150["   ⚙️ ОПЕРАЦИЯ    " ]
  node_149 -- " <font color='black'><b>далее</b></font> " ----> node_150
  class node_150 op_style
  node_151(["   🔍 this   " ])
  node_150 -- " <font color='black'><b>далее</b></font> " ----> node_151
  node_152(["   🔍 priority   " ])
  node_150 -- " <font color='black'><b>далее</b></font> " ----> node_152
  node_153["   💎 2   "]
  node_149 -- " <font color='black'><b>далее</b></font> " ----> node_153
  node_154["   📂 БЛОК КОДА { }   " ]
  node_148 -- " <font color='black'><b>далее</b></font> " ----> node_154
  node_155["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_154 -- " <font color='black'><b>далее</b></font> " ----> node_155
  class node_155 op_style
  node_156(["   🔍 priorityStr   " ])
  node_155 -- " <font color='black'><b>далее</b></font> " ----> node_156
  node_157["   💎 Medium   "]
  node_155 -- " <font color='black'><b>далее</b></font> " ----> node_157
  node_158["   📂 БЛОК КОДА { }   " ]
  node_148 -- " <font color='black'><b>далее</b></font> " ----> node_158
  node_159["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_158 -- " <font color='black'><b>далее</b></font> " ----> node_159
  class node_159 op_style
  node_160(["   🔍 priorityStr   " ])
  node_159 -- " <font color='black'><b>далее</b></font> " ----> node_160
  node_161["   💎 Low   "]
  node_159 -- " <font color='black'><b>далее</b></font> " ----> node_161
  node_162[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_126 -- " <font color='black'><b>далее</b></font> " ----> node_162
  node_163["   ➕ СЛОЖИТЬ (+)    " ]
  node_162 -- " <font color='black'><b>далее</b></font> " ----> node_163
  class node_163 op_style
  node_164["   ➕ СЛОЖИТЬ (+)    " ]
  node_163 -- " <font color='black'><b>далее</b></font> " ----> node_164
  class node_164 op_style
  node_165["   ➕ СЛОЖИТЬ (+)    " ]
  node_164 -- " <font color='black'><b>далее</b></font> " ----> node_165
  class node_165 op_style
  node_166["   ➕ СЛОЖИТЬ (+)    " ]
  node_165 -- " <font color='black'><b>далее</b></font> " ----> node_166
  class node_166 op_style
  node_167["   ➕ СЛОЖИТЬ (+)    " ]
  node_166 -- " <font color='black'><b>далее</b></font> " ----> node_167
  class node_167 op_style
  node_168["   ➕ СЛОЖИТЬ (+)    " ]
  node_167 -- " <font color='black'><b>далее</b></font> " ----> node_168
  class node_168 op_style
  node_169["   ➕ СЛОЖИТЬ (+)    " ]
  node_168 -- " <font color='black'><b>далее</b></font> " ----> node_169
  class node_169 op_style
  node_170["   💎 [   "]
  node_169 -- " <font color='black'><b>далее</b></font> " ----> node_170
  node_171["   ⚙️ ОПЕРАЦИЯ    " ]
  node_169 -- " <font color='black'><b>далее</b></font> " ----> node_171
  class node_171 op_style
  node_172(["   🔍 this   " ])
  node_171 -- " <font color='black'><b>далее</b></font> " ----> node_172
  node_173(["   🔍 id   " ])
  node_171 -- " <font color='black'><b>далее</b></font> " ----> node_173
  node_174["   💎 ]    "]
  node_168 -- " <font color='black'><b>далее</b></font> " ----> node_174
  node_175(["   🔍 priorityStr   " ])
  node_167 -- " <font color='black'><b>далее</b></font> " ----> node_175
  node_176["   💎  |    "]
  node_166 -- " <font color='black'><b>далее</b></font> " ----> node_176
  node_177(["   🔍 status   " ])
  node_165 -- " <font color='black'><b>далее</b></font> " ----> node_177
  node_178["   💎  |    "]
  node_164 -- " <font color='black'><b>далее</b></font> " ----> node_178
  node_179["   ⚙️ ОПЕРАЦИЯ    " ]
  node_163 -- " <font color='black'><b>далее</b></font> " ----> node_179
  class node_179 op_style
  node_180(["   🔍 this   " ])
  node_179 -- " <font color='black'><b>далее</b></font> " ----> node_180
  node_181(["   🔍 title   " ])
  node_179 -- " <font color='black'><b>далее</b></font> " ----> node_181
  node_182[["   🏛️ КЛАСС: User   " ]]
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_182
  class node_182 root_style
  node_183(["    private ПОЛЕ   " ])
  node_182 -- " <font color='black'><b>член_класса</b></font> " ----> node_183
  class node_183 var_style
  node_184{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_183 -- " <font color='black'><b>далее</b></font> " ----> node_184
  class node_184 var_style
  node_185(["   ИМЯ: id
Тип: auto   " ])
  node_184 -- " <font color='black'><b>память</b></font> " ----> node_185
  node_186(["    public ПОЛЕ   " ])
  node_182 -- " <font color='black'><b>член_класса</b></font> " ----> node_186
  class node_186 var_style
  node_187{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_186 -- " <font color='black'><b>далее</b></font> " ----> node_187
  class node_187 var_style
  node_188(["   ИМЯ: name
Тип: auto   " ])
  node_187 -- " <font color='black'><b>память</b></font> " ----> node_188
  node_189(["    private ПОЛЕ   " ])
  node_182 -- " <font color='black'><b>член_класса</b></font> " ----> node_189
  class node_189 var_style
  node_190{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_189 -- " <font color='black'><b>далее</b></font> " ----> node_190
  class node_190 var_style
  node_191(["   ИМЯ: tasks
Тип: auto   " ])
  node_190 -- " <font color='black'><b>память</b></font> " ----> node_191
  node_192(("    public МЕТОД: new   " ))
  node_182 -- " <font color='black'><b>член_класса</b></font> " ----> node_192
  class node_192 func_style
  node_193(("   🔨 ФУНКЦИЯ: new
Вернет: auto   " ))
  node_192 -- " <font color='black'><b>далее</b></font> " ----> node_193
  class node_193 func_style
  node_194(["   АРГ: id (auto)   " ])
  node_193 -- " <font color='black'><b>сигнатура</b></font> " ----> node_194
  node_195(["   АРГ: name (auto)   " ])
  node_193 -- " <font color='black'><b>сигнатура</b></font> " ----> node_195
  node_196["   📂 БЛОК КОДА { }   " ]
  node_193 -- " <font color='black'><b>далее</b></font> " ----> node_196
  node_197["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_196 -- " <font color='black'><b>далее</b></font> " ----> node_197
  class node_197 op_style
  node_198["   ⚙️ ОПЕРАЦИЯ    " ]
  node_197 -- " <font color='black'><b>далее</b></font> " ----> node_198
  class node_198 op_style
  node_199(["   🔍 this   " ])
  node_198 -- " <font color='black'><b>далее</b></font> " ----> node_199
  node_200(["   🔍 id   " ])
  node_198 -- " <font color='black'><b>далее</b></font> " ----> node_200
  node_201(["   🔍 id   " ])
  node_197 -- " <font color='black'><b>далее</b></font> " ----> node_201
  node_202["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_196 -- " <font color='black'><b>далее</b></font> " ----> node_202
  class node_202 op_style
  node_203["   ⚙️ ОПЕРАЦИЯ    " ]
  node_202 -- " <font color='black'><b>далее</b></font> " ----> node_203
  class node_203 op_style
  node_204(["   🔍 this   " ])
  node_203 -- " <font color='black'><b>далее</b></font> " ----> node_204
  node_205(["   🔍 name   " ])
  node_203 -- " <font color='black'><b>далее</b></font> " ----> node_205
  node_206(["   🔍 name   " ])
  node_202 -- " <font color='black'><b>далее</b></font> " ----> node_206
  node_207["   ⚙️ ОПЕРАЦИЯ    " ]
  node_196 -- " <font color='black'><b>далее</b></font> " ----> node_207
  class node_207 op_style
  node_208(["   🔍 this   " ])
  node_207 -- " <font color='black'><b>далее</b></font> " ----> node_208
  node_209(["   🔍 tasks   " ])
  node_207 -- " <font color='black'><b>далее</b></font> " ----> node_209
  node_210(("    public МЕТОД: id «get»   " ))
  node_182 -- " <font color='black'><b>член_класса</b></font> " ----> node_210
  class node_210 func_style
  node_211(("   🔨 ФУНКЦИЯ: id
Вернет: auto   " ))
  node_210 -- " <font color='black'><b>далее</b></font> " ----> node_211
  class node_211 func_style
  node_212["   📂 БЛОК КОДА { }   " ]
  node_211 -- " <font color='black'><b>далее</b></font> " ----> node_212
  node_213[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_212 -- " <font color='black'><b>далее</b></font> " ----> node_213
  node_214["   ⚙️ ОПЕРАЦИЯ    " ]
  node_213 -- " <font color='black'><b>далее</b></font> " ----> node_214
  class node_214 op_style
  node_215(["   🔍 this   " ])
  node_214 -- " <font color='black'><b>далее</b></font> " ----> node_215
  node_216(["   🔍 id   " ])
  node_214 -- " <font color='black'><b>далее</b></font> " ----> node_216
  node_217(("    public МЕТОД: name «get»   " ))
  node_182 -- " <font color='black'><b>член_класса</b></font> " ----> node_217
  class node_217 func_style
  node_218(("   🔨 ФУНКЦИЯ: name
Вернет: auto   " ))
  node_217 -- " <font color='black'><b>далее</b></font> " ----> node_218
  class node_218 func_style
  node_219["   📂 БЛОК КОДА { }   " ]
  node_218 -- " <font color='black'><b>далее</b></font> " ----> node_219
  node_220[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_219 -- " <font color='black'><b>далее</b></font> " ----> node_220
  node_221["   ⚙️ ОПЕРАЦИЯ    " ]
  node_220 -- " <font color='black'><b>далее</b></font> " ----> node_221
  class node_221 op_style
  node_222(["   🔍 this   " ])
  node_221 -- " <font color='black'><b>далее</b></font> " ----> node_222
  node_223(["   🔍 name   " ])
  node_221 -- " <font color='black'><b>далее</b></font> " ----> node_223
  node_224(("    public МЕТОД: tasks «get»   " ))
  node_182 -- " <font color='black'><b>член_класса</b></font> " ----> node_224
  class node_224 func_style
  node_225(("   🔨 ФУНКЦИЯ: tasks
Вернет: auto   " ))
  node_224 -- " <font color='black'><b>далее</b></font> " ----> node_225
  class node_225 func_style
  node_226["   📂 БЛОК КОДА { }   " ]
  node_225 -- " <font color='black'><b>далее</b></font> " ----> node_226
  node_227[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_226 -- " <font color='black'><b>далее</b></font> " ----> node_227
  node_228["   ⚙️ ОПЕРАЦИЯ    " ]
  node_227 -- " <font color='black'><b>далее</b></font> " ----> node_228
  class node_228 op_style
  node_229(["   🔍 this   " ])
  node_228 -- " <font color='black'><b>далее</b></font> " ----> node_229
  node_230(["   🔍 tasks   " ])
  node_228 -- " <font color='black'><b>далее</b></font> " ----> node_230
  node_231(("    public МЕТОД: addTask   " ))
  node_182 -- " <font color='black'><b>член_класса</b></font> " ----> node_231
  class node_231 func_style
  node_232(("   🔨 ФУНКЦИЯ: addTask
Вернет: auto   " ))
  node_231 -- " <font color='black'><b>далее</b></font> " ----> node_232
  class node_232 func_style
  node_233(["   АРГ: title (auto)   " ])
  node_232 -- " <font color='black'><b>сигнатура</b></font> " ----> node_233
  node_234(["   АРГ: description (auto)   " ])
  node_232 -- " <font color='black'><b>сигнатура</b></font> " ----> node_234
  node_235(["   АРГ: priority (auto)   " ])
  node_232 -- " <font color='black'><b>сигнатура</b></font> " ----> node_235
  node_236["   📂 БЛОК КОДА { }   " ]
  node_232 -- " <font color='black'><b>далее</b></font> " ----> node_236
  node_237{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_236 -- " <font color='black'><b>далее</b></font> " ----> node_237
  class node_237 var_style
  node_238(["   ИМЯ: newId
Тип: auto   " ])
  node_237 -- " <font color='black'><b>память</b></font> " ----> node_238
  node_239["   ➕ СЛОЖИТЬ (+)    " ]
  node_238 -- " <font color='black'><b>далее</b></font> " ----> node_239
  class node_239 op_style
  node_240(["   🚀 ВЫЗОВ: len()   " ])
  node_239 -- " <font color='black'><b>далее</b></font> " ----> node_240
  class node_240 func_style
  node_241["   ⚙️ ОПЕРАЦИЯ    " ]
  node_240 -- " <font color='black'><b>далее</b></font> " ----> node_241
  class node_241 op_style
  node_242(["   🔍 this   " ])
  node_241 -- " <font color='black'><b>далее</b></font> " ----> node_242
  node_243(["   🔍 tasks   " ])
  node_241 -- " <font color='black'><b>далее</b></font> " ----> node_243
  node_244["   💎 1   "]
  node_239 -- " <font color='black'><b>далее</b></font> " ----> node_244
  node_245{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_236 -- " <font color='black'><b>далее</b></font> " ----> node_245
  class node_245 var_style
  node_246(["   ИМЯ: task
Тип: auto   " ])
  node_245 -- " <font color='black'><b>память</b></font> " ----> node_246
  node_247(["   🚀 ВЫЗОВ: Task()   " ])
  node_246 -- " <font color='black'><b>далее</b></font> " ----> node_247
  class node_247 func_style
  node_248(["   🔍 newId   " ])
  node_247 -- " <font color='black'><b>далее</b></font> " ----> node_248
  node_249(["   🔍 title   " ])
  node_247 -- " <font color='black'><b>далее</b></font> " ----> node_249
  node_250(["   🔍 description   " ])
  node_247 -- " <font color='black'><b>далее</b></font> " ----> node_250
  node_251(["   🔍 priority   " ])
  node_247 -- " <font color='black'><b>далее</b></font> " ----> node_251
  node_252["   ⚙️ ОПЕРАЦИЯ    " ]
  node_236 -- " <font color='black'><b>далее</b></font> " ----> node_252
  class node_252 op_style
  node_253["   ⚙️ ОПЕРАЦИЯ    " ]
  node_252 -- " <font color='black'><b>далее</b></font> " ----> node_253
  class node_253 op_style
  node_254(["   🔍 this   " ])
  node_253 -- " <font color='black'><b>далее</b></font> " ----> node_254
  node_255(["   🔍 tasks   " ])
  node_253 -- " <font color='black'><b>далее</b></font> " ----> node_255
  node_256(["   🚀 ВЫЗОВ: push()   " ])
  node_252 -- " <font color='black'><b>далее</b></font> " ----> node_256
  class node_256 func_style
  node_257(["   🔍 task   " ])
  node_256 -- " <font color='black'><b>далее</b></font> " ----> node_257
  node_258(["   🚀 ВЫЗОВ: print()   " ])
  node_236 -- " <font color='black'><b>далее</b></font> " ----> node_258
  class node_258 func_style
  node_259["   ➕ СЛОЖИТЬ (+)    " ]
  node_258 -- " <font color='black'><b>далее</b></font> " ----> node_259
  class node_259 op_style
  node_260["   💎 Task added:    "]
  node_259 -- " <font color='black'><b>далее</b></font> " ----> node_260
  node_261["   ⚙️ ОПЕРАЦИЯ    " ]
  node_259 -- " <font color='black'><b>далее</b></font> " ----> node_261
  class node_261 op_style
  node_262(["   🔍 task   " ])
  node_261 -- " <font color='black'><b>далее</b></font> " ----> node_262
  node_263(["   🚀 ВЫЗОВ: toString()   " ])
  node_261 -- " <font color='black'><b>далее</b></font> " ----> node_263
  class node_263 func_style
  node_264[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_236 -- " <font color='black'><b>далее</b></font> " ----> node_264
  node_265(["   🔍 task   " ])
  node_264 -- " <font color='black'><b>далее</b></font> " ----> node_265
  node_266(("    public МЕТОД: removeTask   " ))
  node_182 -- " <font color='black'><b>член_класса</b></font> " ----> node_266
  class node_266 func_style
  node_267(("   🔨 ФУНКЦИЯ: removeTask
Вернет: auto   " ))
  node_266 -- " <font color='black'><b>далее</b></font> " ----> node_267
  class node_267 func_style
  node_268(["   АРГ: taskId (auto)   " ])
  node_267 -- " <font color='black'><b>сигнатура</b></font> " ----> node_268
  node_269["   📂 БЛОК КОДА { }   " ]
  node_267 -- " <font color='black'><b>далее</b></font> " ----> node_269
  node_270{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_269 -- " <font color='black'><b>далее</b></font> " ----> node_270
  class node_270 var_style
  node_271(["   ИМЯ: newTasks
Тип: auto   " ])
  node_270 -- " <font color='black'><b>память</b></font> " ----> node_271
  node_272{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_269 -- " <font color='black'><b>далее</b></font> " ----> node_272
  class node_272 var_style
  node_273(["   ИМЯ: found
Тип: auto   " ])
  node_272 -- " <font color='black'><b>память</b></font> " ----> node_273
  node_274["   💎 false   "]
  node_273 -- " <font color='black'><b>далее</b></font> " ----> node_274
  node_275{{"   ♻️ ЦИКЛ: for (task)   " }}
  node_269 -- " <font color='black'><b>далее</b></font> " ----> node_275
  class node_275 logic_style
  node_276["   ⚙️ ОПЕРАЦИЯ    " ]
  node_275 -- " <font color='black'><b>далее</b></font> " ----> node_276
  class node_276 op_style
  node_277(["   🔍 this   " ])
  node_276 -- " <font color='black'><b>далее</b></font> " ----> node_277
  node_278(["   🔍 tasks   " ])
  node_276 -- " <font color='black'><b>далее</b></font> " ----> node_278
  node_279["   📂 БЛОК КОДА { }   " ]
  node_275 -- " <font color='black'><b>далее</b></font> " ----> node_279
  node_280{"   ❓ ЕСЛИ (if)   " }
  node_279 -- " <font color='black'><b>далее</b></font> " ----> node_280
  class node_280 logic_style
  node_281["   🚫 НЕ РАВНО (!=)    " ]
  node_280 -- " <font color='black'><b>далее</b></font> " ----> node_281
  class node_281 op_style
  node_282["   ⚙️ ОПЕРАЦИЯ    " ]
  node_281 -- " <font color='black'><b>далее</b></font> " ----> node_282
  class node_282 op_style
  node_283(["   🔍 task   " ])
  node_282 -- " <font color='black'><b>далее</b></font> " ----> node_283
  node_284(["   🚀 ВЫЗОВ: id()   " ])
  node_282 -- " <font color='black'><b>далее</b></font> " ----> node_284
  class node_284 func_style
  node_285(["   🔍 taskId   " ])
  node_281 -- " <font color='black'><b>далее</b></font> " ----> node_285
  node_286["   📂 БЛОК КОДА { }   " ]
  node_280 -- " <font color='black'><b>далее</b></font> " ----> node_286
  node_287["   ⚙️ ОПЕРАЦИЯ    " ]
  node_286 -- " <font color='black'><b>далее</b></font> " ----> node_287
  class node_287 op_style
  node_288(["   🔍 newTasks   " ])
  node_287 -- " <font color='black'><b>далее</b></font> " ----> node_288
  node_289(["   🚀 ВЫЗОВ: push()   " ])
  node_287 -- " <font color='black'><b>далее</b></font> " ----> node_289
  class node_289 func_style
  node_290(["   🔍 task   " ])
  node_289 -- " <font color='black'><b>далее</b></font> " ----> node_290
  node_291["   📂 БЛОК КОДА { }   " ]
  node_280 -- " <font color='black'><b>далее</b></font> " ----> node_291
  node_292["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_291 -- " <font color='black'><b>далее</b></font> " ----> node_292
  class node_292 op_style
  node_293(["   🔍 found   " ])
  node_292 -- " <font color='black'><b>далее</b></font> " ----> node_293
  node_294["   💎 true   "]
  node_292 -- " <font color='black'><b>далее</b></font> " ----> node_294
  node_295{"   ❓ ЕСЛИ (if)   " }
  node_269 -- " <font color='black'><b>далее</b></font> " ----> node_295
  class node_295 logic_style
  node_296(["   🔍 found   " ])
  node_295 -- " <font color='black'><b>далее</b></font> " ----> node_296
  node_297["   📂 БЛОК КОДА { }   " ]
  node_295 -- " <font color='black'><b>далее</b></font> " ----> node_297
  node_298["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_297 -- " <font color='black'><b>далее</b></font> " ----> node_298
  class node_298 op_style
  node_299["   ⚙️ ОПЕРАЦИЯ    " ]
  node_298 -- " <font color='black'><b>далее</b></font> " ----> node_299
  class node_299 op_style
  node_300(["   🔍 this   " ])
  node_299 -- " <font color='black'><b>далее</b></font> " ----> node_300
  node_301(["   🔍 tasks   " ])
  node_299 -- " <font color='black'><b>далее</b></font> " ----> node_301
  node_302(["   🔍 newTasks   " ])
  node_298 -- " <font color='black'><b>далее</b></font> " ----> node_302
  node_303(["   🚀 ВЫЗОВ: print()   " ])
  node_297 -- " <font color='black'><b>далее</b></font> " ----> node_303
  class node_303 func_style
  node_304["   ➕ СЛОЖИТЬ (+)    " ]
  node_303 -- " <font color='black'><b>далее</b></font> " ----> node_304
  class node_304 op_style
  node_305["   ➕ СЛОЖИТЬ (+)    " ]
  node_304 -- " <font color='black'><b>далее</b></font> " ----> node_305
  class node_305 op_style
  node_306["   💎 Task    "]
  node_305 -- " <font color='black'><b>далее</b></font> " ----> node_306
  node_307(["   🔍 taskId   " ])
  node_305 -- " <font color='black'><b>далее</b></font> " ----> node_307
  node_308["   💎  removed   "]
  node_304 -- " <font color='black'><b>далее</b></font> " ----> node_308
  node_309[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_297 -- " <font color='black'><b>далее</b></font> " ----> node_309
  node_310["   💎 true   "]
  node_309 -- " <font color='black'><b>далее</b></font> " ----> node_310
  node_311["   📂 БЛОК КОДА { }   " ]
  node_295 -- " <font color='black'><b>далее</b></font> " ----> node_311
  node_312(["   🚀 ВЫЗОВ: print()   " ])
  node_311 -- " <font color='black'><b>далее</b></font> " ----> node_312
  class node_312 func_style
  node_313["   ➕ СЛОЖИТЬ (+)    " ]
  node_312 -- " <font color='black'><b>далее</b></font> " ----> node_313
  class node_313 op_style
  node_314["   ➕ СЛОЖИТЬ (+)    " ]
  node_313 -- " <font color='black'><b>далее</b></font> " ----> node_314
  class node_314 op_style
  node_315["   💎 Task    "]
  node_314 -- " <font color='black'><b>далее</b></font> " ----> node_315
  node_316(["   🔍 taskId   " ])
  node_314 -- " <font color='black'><b>далее</b></font> " ----> node_316
  node_317["   💎  not found   "]
  node_313 -- " <font color='black'><b>далее</b></font> " ----> node_317
  node_318[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_311 -- " <font color='black'><b>далее</b></font> " ----> node_318
  node_319["   💎 false   "]
  node_318 -- " <font color='black'><b>далее</b></font> " ----> node_319
  node_320(("    public МЕТОД: findTaskById   " ))
  node_182 -- " <font color='black'><b>член_класса</b></font> " ----> node_320
  class node_320 func_style
  node_321(("   🔨 ФУНКЦИЯ: findTaskById
Вернет: auto   " ))
  node_320 -- " <font color='black'><b>далее</b></font> " ----> node_321
  class node_321 func_style
  node_322(["   АРГ: taskId (auto)   " ])
  node_321 -- " <font color='black'><b>сигнатура</b></font> " ----> node_322
  node_323["   📂 БЛОК КОДА { }   " ]
  node_321 -- " <font color='black'><b>далее</b></font> " ----> node_323
  node_324{{"   ♻️ ЦИКЛ: for (task)   " }}
  node_323 -- " <font color='black'><b>далее</b></font> " ----> node_324
  class node_324 logic_style
  node_325["   ⚙️ ОПЕРАЦИЯ    " ]
  node_324 -- " <font color='black'><b>далее</b></font> " ----> node_325
  class node_325 op_style
  node_326(["   🔍 this   " ])
  node_325 -- " <font color='black'><b>далее</b></font> " ----> node_326
  node_327(["   🔍 tasks   " ])
  node_325 -- " <font color='black'><b>далее</b></font> " ----> node_327
  node_328["   📂 БЛОК КОДА { }   " ]
  node_324 -- " <font color='black'><b>далее</b></font> " ----> node_328
  node_329{"   ❓ ЕСЛИ (if)   " }
  node_328 -- " <font color='black'><b>далее</b></font> " ----> node_329
  class node_329 logic_style
  node_330["   ⚖️ РАВНО (==)    " ]
  node_329 -- " <font color='black'><b>далее</b></font> " ----> node_330
  class node_330 op_style
  node_331["   ⚙️ ОПЕРАЦИЯ    " ]
  node_330 -- " <font color='black'><b>далее</b></font> " ----> node_331
  class node_331 op_style
  node_332(["   🔍 task   " ])
  node_331 -- " <font color='black'><b>далее</b></font> " ----> node_332
  node_333(["   🚀 ВЫЗОВ: id()   " ])
  node_331 -- " <font color='black'><b>далее</b></font> " ----> node_333
  class node_333 func_style
  node_334(["   🔍 taskId   " ])
  node_330 -- " <font color='black'><b>далее</b></font> " ----> node_334
  node_335["   📂 БЛОК КОДА { }   " ]
  node_329 -- " <font color='black'><b>далее</b></font> " ----> node_335
  node_336[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_335 -- " <font color='black'><b>далее</b></font> " ----> node_336
  node_337(["   🔍 task   " ])
  node_336 -- " <font color='black'><b>далее</b></font> " ----> node_337
  node_338[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_323 -- " <font color='black'><b>далее</b></font> " ----> node_338
  node_339["   💎 null   "]
  node_338 -- " <font color='black'><b>далее</b></font> " ----> node_339
  node_340(("    public МЕТОД: findTasksByPriority   " ))
  node_182 -- " <font color='black'><b>член_класса</b></font> " ----> node_340
  class node_340 func_style
  node_341(("   🔨 ФУНКЦИЯ: findTasksByPriority
Вернет: auto   " ))
  node_340 -- " <font color='black'><b>далее</b></font> " ----> node_341
  class node_341 func_style
  node_342(["   АРГ: priority (auto)   " ])
  node_341 -- " <font color='black'><b>сигнатура</b></font> " ----> node_342
  node_343["   📂 БЛОК КОДА { }   " ]
  node_341 -- " <font color='black'><b>далее</b></font> " ----> node_343
  node_344{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_343 -- " <font color='black'><b>далее</b></font> " ----> node_344
  class node_344 var_style
  node_345(["   ИМЯ: results
Тип: auto   " ])
  node_344 -- " <font color='black'><b>память</b></font> " ----> node_345
  node_346{{"   ♻️ ЦИКЛ: for (task)   " }}
  node_343 -- " <font color='black'><b>далее</b></font> " ----> node_346
  class node_346 logic_style
  node_347["   ⚙️ ОПЕРАЦИЯ    " ]
  node_346 -- " <font color='black'><b>далее</b></font> " ----> node_347
  class node_347 op_style
  node_348(["   🔍 this   " ])
  node_347 -- " <font color='black'><b>далее</b></font> " ----> node_348
  node_349(["   🔍 tasks   " ])
  node_347 -- " <font color='black'><b>далее</b></font> " ----> node_349
  node_350["   📂 БЛОК КОДА { }   " ]
  node_346 -- " <font color='black'><b>далее</b></font> " ----> node_350
  node_351{"   ❓ ЕСЛИ (if)   " }
  node_350 -- " <font color='black'><b>далее</b></font> " ----> node_351
  class node_351 logic_style
  node_352["   ⚖️ РАВНО (==)    " ]
  node_351 -- " <font color='black'><b>далее</b></font> " ----> node_352
  class node_352 op_style
  node_353["   ⚙️ ОПЕРАЦИЯ    " ]
  node_352 -- " <font color='black'><b>далее</b></font> " ----> node_353
  class node_353 op_style
  node_354(["   🔍 task   " ])
  node_353 -- " <font color='black'><b>далее</b></font> " ----> node_354
  node_355(["   🚀 ВЫЗОВ: priority()   " ])
  node_353 -- " <font color='black'><b>далее</b></font> " ----> node_355
  class node_355 func_style
  node_356(["   🔍 priority   " ])
  node_352 -- " <font color='black'><b>далее</b></font> " ----> node_356
  node_357["   📂 БЛОК КОДА { }   " ]
  node_351 -- " <font color='black'><b>далее</b></font> " ----> node_357
  node_358["   ⚙️ ОПЕРАЦИЯ    " ]
  node_357 -- " <font color='black'><b>далее</b></font> " ----> node_358
  class node_358 op_style
  node_359(["   🔍 results   " ])
  node_358 -- " <font color='black'><b>далее</b></font> " ----> node_359
  node_360(["   🚀 ВЫЗОВ: push()   " ])
  node_358 -- " <font color='black'><b>далее</b></font> " ----> node_360
  class node_360 func_style
  node_361(["   🔍 task   " ])
  node_360 -- " <font color='black'><b>далее</b></font> " ----> node_361
  node_362[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_343 -- " <font color='black'><b>далее</b></font> " ----> node_362
  node_363(["   🔍 results   " ])
  node_362 -- " <font color='black'><b>далее</b></font> " ----> node_363
  node_364(("    public МЕТОД: findTasksByStatus   " ))
  node_182 -- " <font color='black'><b>член_класса</b></font> " ----> node_364
  class node_364 func_style
  node_365(("   🔨 ФУНКЦИЯ: findTasksByStatus
Вернет: auto   " ))
  node_364 -- " <font color='black'><b>далее</b></font> " ----> node_365
  class node_365 func_style
  node_366(["   АРГ: completed (auto)   " ])
  node_365 -- " <font color='black'><b>сигнатура</b></font> " ----> node_366
  node_367["   📂 БЛОК КОДА { }   " ]
  node_365 -- " <font color='black'><b>далее</b></font> " ----> node_367
  node_368{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_367 -- " <font color='black'><b>далее</b></font> " ----> node_368
  class node_368 var_style
  node_369(["   ИМЯ: results
Тип: auto   " ])
  node_368 -- " <font color='black'><b>память</b></font> " ----> node_369
  node_370{{"   ♻️ ЦИКЛ: for (task)   " }}
  node_367 -- " <font color='black'><b>далее</b></font> " ----> node_370
  class node_370 logic_style
  node_371["   ⚙️ ОПЕРАЦИЯ    " ]
  node_370 -- " <font color='black'><b>далее</b></font> " ----> node_371
  class node_371 op_style
  node_372(["   🔍 this   " ])
  node_371 -- " <font color='black'><b>далее</b></font> " ----> node_372
  node_373(["   🔍 tasks   " ])
  node_371 -- " <font color='black'><b>далее</b></font> " ----> node_373
  node_374["   📂 БЛОК КОДА { }   " ]
  node_370 -- " <font color='black'><b>далее</b></font> " ----> node_374
  node_375{"   ❓ ЕСЛИ (if)   " }
  node_374 -- " <font color='black'><b>далее</b></font> " ----> node_375
  class node_375 logic_style
  node_376["   ⚖️ РАВНО (==)    " ]
  node_375 -- " <font color='black'><b>далее</b></font> " ----> node_376
  class node_376 op_style
  node_377["   ⚙️ ОПЕРАЦИЯ    " ]
  node_376 -- " <font color='black'><b>далее</b></font> " ----> node_377
  class node_377 op_style
  node_378(["   🔍 task   " ])
  node_377 -- " <font color='black'><b>далее</b></font> " ----> node_378
  node_379(["   🚀 ВЫЗОВ: completed()   " ])
  node_377 -- " <font color='black'><b>далее</b></font> " ----> node_379
  class node_379 func_style
  node_380(["   🔍 completed   " ])
  node_376 -- " <font color='black'><b>далее</b></font> " ----> node_380
  node_381["   📂 БЛОК КОДА { }   " ]
  node_375 -- " <font color='black'><b>далее</b></font> " ----> node_381
  node_382["   ⚙️ ОПЕРАЦИЯ    " ]
  node_381 -- " <font color='black'><b>далее</b></font> " ----> node_382
  class node_382 op_style
  node_383(["   🔍 results   " ])
  node_382 -- " <font color='black'><b>далее</b></font> " ----> node_383
  node_384(["   🚀 ВЫЗОВ: push()   " ])
  node_382 -- " <font color='black'><b>далее</b></font> " ----> node_384
  class node_384 func_style
  node_385(["   🔍 task   " ])
  node_384 -- " <font color='black'><b>далее</b></font> " ----> node_385
  node_386[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_367 -- " <font color='black'><b>далее</b></font> " ----> node_386
  node_387(["   🔍 results   " ])
  node_386 -- " <font color='black'><b>далее</b></font> " ----> node_387
  node_388(("    public МЕТОД: listAllTasks   " ))
  node_182 -- " <font color='black'><b>член_класса</b></font> " ----> node_388
  class node_388 func_style
  node_389(("   🔨 ФУНКЦИЯ: listAllTasks
Вернет: auto   " ))
  node_388 -- " <font color='black'><b>далее</b></font> " ----> node_389
  class node_389 func_style
  node_390["   📂 БЛОК КОДА { }   " ]
  node_389 -- " <font color='black'><b>далее</b></font> " ----> node_390
  node_391(["   🚀 ВЫЗОВ: print()   " ])
  node_390 -- " <font color='black'><b>далее</b></font> " ----> node_391
  class node_391 func_style
  node_392["   💎     "]
  node_391 -- " <font color='black'><b>далее</b></font> " ----> node_392
  node_393(["   🚀 ВЫЗОВ: print()   " ])
  node_390 -- " <font color='black'><b>далее</b></font> " ----> node_393
  class node_393 func_style
  node_394["   ➕ СЛОЖИТЬ (+)    " ]
  node_393 -- " <font color='black'><b>далее</b></font> " ----> node_394
  class node_394 op_style
  node_395["   ➕ СЛОЖИТЬ (+)    " ]
  node_394 -- " <font color='black'><b>далее</b></font> " ----> node_395
  class node_395 op_style
  node_396["   💎 === Tasks for user:    "]
  node_395 -- " <font color='black'><b>далее</b></font> " ----> node_396
  node_397["   ⚙️ ОПЕРАЦИЯ    " ]
  node_395 -- " <font color='black'><b>далее</b></font> " ----> node_397
  class node_397 op_style
  node_398(["   🔍 this   " ])
  node_397 -- " <font color='black'><b>далее</b></font> " ----> node_398
  node_399(["   🔍 name   " ])
  node_397 -- " <font color='black'><b>далее</b></font> " ----> node_399
  node_400["   💎  ===   "]
  node_394 -- " <font color='black'><b>далее</b></font> " ----> node_400
  node_401{"   ❓ ЕСЛИ (if)   " }
  node_390 -- " <font color='black'><b>далее</b></font> " ----> node_401
  class node_401 logic_style
  node_402["   ⚖️ РАВНО (==)    " ]
  node_401 -- " <font color='black'><b>далее</b></font> " ----> node_402
  class node_402 op_style
  node_403(["   🚀 ВЫЗОВ: len()   " ])
  node_402 -- " <font color='black'><b>далее</b></font> " ----> node_403
  class node_403 func_style
  node_404["   ⚙️ ОПЕРАЦИЯ    " ]
  node_403 -- " <font color='black'><b>далее</b></font> " ----> node_404
  class node_404 op_style
  node_405(["   🔍 this   " ])
  node_404 -- " <font color='black'><b>далее</b></font> " ----> node_405
  node_406(["   🔍 tasks   " ])
  node_404 -- " <font color='black'><b>далее</b></font> " ----> node_406
  node_407["   💎 0   "]
  node_402 -- " <font color='black'><b>далее</b></font> " ----> node_407
  node_408["   📂 БЛОК КОДА { }   " ]
  node_401 -- " <font color='black'><b>далее</b></font> " ----> node_408
  node_409(["   🚀 ВЫЗОВ: print()   " ])
  node_408 -- " <font color='black'><b>далее</b></font> " ----> node_409
  class node_409 func_style
  node_410["   💎 No tasks found   "]
  node_409 -- " <font color='black'><b>далее</b></font> " ----> node_410
  node_411["   📂 БЛОК КОДА { }   " ]
  node_401 -- " <font color='black'><b>далее</b></font> " ----> node_411
  node_412{{"   ♻️ ЦИКЛ: for (task)   " }}
  node_411 -- " <font color='black'><b>далее</b></font> " ----> node_412
  class node_412 logic_style
  node_413["   ⚙️ ОПЕРАЦИЯ    " ]
  node_412 -- " <font color='black'><b>далее</b></font> " ----> node_413
  class node_413 op_style
  node_414(["   🔍 this   " ])
  node_413 -- " <font color='black'><b>далее</b></font> " ----> node_414
  node_415(["   🔍 tasks   " ])
  node_413 -- " <font color='black'><b>далее</b></font> " ----> node_415
  node_416["   📂 БЛОК КОДА { }   " ]
  node_412 -- " <font color='black'><b>далее</b></font> " ----> node_416
  node_417(["   🚀 ВЫЗОВ: print()   " ])
  node_416 -- " <font color='black'><b>далее</b></font> " ----> node_417
  class node_417 func_style
  node_418["   ⚙️ ОПЕРАЦИЯ    " ]
  node_417 -- " <font color='black'><b>далее</b></font> " ----> node_418
  class node_418 op_style
  node_419(["   🔍 task   " ])
  node_418 -- " <font color='black'><b>далее</b></font> " ----> node_419
  node_420(["   🚀 ВЫЗОВ: toString()   " ])
  node_418 -- " <font color='black'><b>далее</b></font> " ----> node_420
  class node_420 func_style
  node_421(["   🚀 ВЫЗОВ: print()   " ])
  node_390 -- " <font color='black'><b>далее</b></font> " ----> node_421
  class node_421 func_style
  node_422["   💎 ==================================   "]
  node_421 -- " <font color='black'><b>далее</b></font> " ----> node_422
  node_423(["   🚀 ВЫЗОВ: print()   " ])
  node_390 -- " <font color='black'><b>далее</b></font> " ----> node_423
  class node_423 func_style
  node_424["   💎     "]
  node_423 -- " <font color='black'><b>далее</b></font> " ----> node_424
  node_425(("    public МЕТОД: listPendingTasks   " ))
  node_182 -- " <font color='black'><b>член_класса</b></font> " ----> node_425
  class node_425 func_style
  node_426(("   🔨 ФУНКЦИЯ: listPendingTasks
Вернет: auto   " ))
  node_425 -- " <font color='black'><b>далее</b></font> " ----> node_426
  class node_426 func_style
  node_427["   📂 БЛОК КОДА { }   " ]
  node_426 -- " <font color='black'><b>далее</b></font> " ----> node_427
  node_428(["   🚀 ВЫЗОВ: print()   " ])
  node_427 -- " <font color='black'><b>далее</b></font> " ----> node_428
  class node_428 func_style
  node_429["   💎     "]
  node_428 -- " <font color='black'><b>далее</b></font> " ----> node_429
  node_430(["   🚀 ВЫЗОВ: print()   " ])
  node_427 -- " <font color='black'><b>далее</b></font> " ----> node_430
  class node_430 func_style
  node_431["   💎 === Pending Tasks ===   "]
  node_430 -- " <font color='black'><b>далее</b></font> " ----> node_431
  node_432{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_427 -- " <font color='black'><b>далее</b></font> " ----> node_432
  class node_432 var_style
  node_433(["   ИМЯ: count
Тип: auto   " ])
  node_432 -- " <font color='black'><b>память</b></font> " ----> node_433
  node_434["   💎 0   "]
  node_433 -- " <font color='black'><b>далее</b></font> " ----> node_434
  node_435{{"   ♻️ ЦИКЛ: for (task)   " }}
  node_427 -- " <font color='black'><b>далее</b></font> " ----> node_435
  class node_435 logic_style
  node_436["   ⚙️ ОПЕРАЦИЯ    " ]
  node_435 -- " <font color='black'><b>далее</b></font> " ----> node_436
  class node_436 op_style
  node_437(["   🔍 this   " ])
  node_436 -- " <font color='black'><b>далее</b></font> " ----> node_437
  node_438(["   🔍 tasks   " ])
  node_436 -- " <font color='black'><b>далее</b></font> " ----> node_438
  node_439["   📂 БЛОК КОДА { }   " ]
  node_435 -- " <font color='black'><b>далее</b></font> " ----> node_439
  node_440{"   ❓ ЕСЛИ (if)   " }
  node_439 -- " <font color='black'><b>далее</b></font> " ----> node_440
  class node_440 logic_style
  node_441(["   ❗ ОТРИЦАНИЕ (!)    " ])
  node_440 -- " <font color='black'><b>далее</b></font> " ----> node_441
  class node_441 op_style
  node_442["   ⚙️ ОПЕРАЦИЯ    " ]
  node_441 -- " <font color='black'><b>далее</b></font> " ----> node_442
  class node_442 op_style
  node_443(["   🔍 task   " ])
  node_442 -- " <font color='black'><b>далее</b></font> " ----> node_443
  node_444(["   🚀 ВЫЗОВ: completed()   " ])
  node_442 -- " <font color='black'><b>далее</b></font> " ----> node_444
  class node_444 func_style
  node_445["   📂 БЛОК КОДА { }   " ]
  node_440 -- " <font color='black'><b>далее</b></font> " ----> node_445
  node_446(["   🚀 ВЫЗОВ: print()   " ])
  node_445 -- " <font color='black'><b>далее</b></font> " ----> node_446
  class node_446 func_style
  node_447["   ⚙️ ОПЕРАЦИЯ    " ]
  node_446 -- " <font color='black'><b>далее</b></font> " ----> node_447
  class node_447 op_style
  node_448(["   🔍 task   " ])
  node_447 -- " <font color='black'><b>далее</b></font> " ----> node_448
  node_449(["   🚀 ВЫЗОВ: toString()   " ])
  node_447 -- " <font color='black'><b>далее</b></font> " ----> node_449
  class node_449 func_style
  node_450["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_445 -- " <font color='black'><b>далее</b></font> " ----> node_450
  class node_450 op_style
  node_451(["   🔍 count   " ])
  node_450 -- " <font color='black'><b>далее</b></font> " ----> node_451
  node_452["   ➕ СЛОЖИТЬ (+)    " ]
  node_450 -- " <font color='black'><b>далее</b></font> " ----> node_452
  class node_452 op_style
  node_453(["   🔍 count   " ])
  node_452 -- " <font color='black'><b>далее</b></font> " ----> node_453
  node_454["   💎 1   "]
  node_452 -- " <font color='black'><b>далее</b></font> " ----> node_454
  node_455{"   ❓ ЕСЛИ (if)   " }
  node_427 -- " <font color='black'><b>далее</b></font> " ----> node_455
  class node_455 logic_style
  node_456["   ⚖️ РАВНО (==)    " ]
  node_455 -- " <font color='black'><b>далее</b></font> " ----> node_456
  class node_456 op_style
  node_457(["   🔍 count   " ])
  node_456 -- " <font color='black'><b>далее</b></font> " ----> node_457
  node_458["   💎 0   "]
  node_456 -- " <font color='black'><b>далее</b></font> " ----> node_458
  node_459["   📂 БЛОК КОДА { }   " ]
  node_455 -- " <font color='black'><b>далее</b></font> " ----> node_459
  node_460(["   🚀 ВЫЗОВ: print()   " ])
  node_459 -- " <font color='black'><b>далее</b></font> " ----> node_460
  class node_460 func_style
  node_461["   💎 No pending tasks   "]
  node_460 -- " <font color='black'><b>далее</b></font> " ----> node_461
  node_462(["   🚀 ВЫЗОВ: print()   " ])
  node_427 -- " <font color='black'><b>далее</b></font> " ----> node_462
  class node_462 func_style
  node_463["   💎 =====================   "]
  node_462 -- " <font color='black'><b>далее</b></font> " ----> node_463
  node_464(["   🚀 ВЫЗОВ: print()   " ])
  node_427 -- " <font color='black'><b>далее</b></font> " ----> node_464
  class node_464 func_style
  node_465["   💎     "]
  node_464 -- " <font color='black'><b>далее</b></font> " ----> node_465
  node_466(("    public МЕТОД: listCompletedTasks   " ))
  node_182 -- " <font color='black'><b>член_класса</b></font> " ----> node_466
  class node_466 func_style
  node_467(("   🔨 ФУНКЦИЯ: listCompletedTasks
Вернет: auto   " ))
  node_466 -- " <font color='black'><b>далее</b></font> " ----> node_467
  class node_467 func_style
  node_468["   📂 БЛОК КОДА { }   " ]
  node_467 -- " <font color='black'><b>далее</b></font> " ----> node_468
  node_469(["   🚀 ВЫЗОВ: print()   " ])
  node_468 -- " <font color='black'><b>далее</b></font> " ----> node_469
  class node_469 func_style
  node_470["   💎     "]
  node_469 -- " <font color='black'><b>далее</b></font> " ----> node_470
  node_471(["   🚀 ВЫЗОВ: print()   " ])
  node_468 -- " <font color='black'><b>далее</b></font> " ----> node_471
  class node_471 func_style
  node_472["   💎 === Completed Tasks ===   "]
  node_471 -- " <font color='black'><b>далее</b></font> " ----> node_472
  node_473{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_468 -- " <font color='black'><b>далее</b></font> " ----> node_473
  class node_473 var_style
  node_474(["   ИМЯ: count
Тип: auto   " ])
  node_473 -- " <font color='black'><b>память</b></font> " ----> node_474
  node_475["   💎 0   "]
  node_474 -- " <font color='black'><b>далее</b></font> " ----> node_475
  node_476{{"   ♻️ ЦИКЛ: for (task)   " }}
  node_468 -- " <font color='black'><b>далее</b></font> " ----> node_476
  class node_476 logic_style
  node_477["   ⚙️ ОПЕРАЦИЯ    " ]
  node_476 -- " <font color='black'><b>далее</b></font> " ----> node_477
  class node_477 op_style
  node_478(["   🔍 this   " ])
  node_477 -- " <font color='black'><b>далее</b></font> " ----> node_478
  node_479(["   🔍 tasks   " ])
  node_477 -- " <font color='black'><b>далее</b></font> " ----> node_479
  node_480["   📂 БЛОК КОДА { }   " ]
  node_476 -- " <font color='black'><b>далее</b></font> " ----> node_480
  node_481{"   ❓ ЕСЛИ (if)   " }
  node_480 -- " <font color='black'><b>далее</b></font> " ----> node_481
  class node_481 logic_style
  node_482["   ⚙️ ОПЕРАЦИЯ    " ]
  node_481 -- " <font color='black'><b>далее</b></font> " ----> node_482
  class node_482 op_style
  node_483(["   🔍 task   " ])
  node_482 -- " <font color='black'><b>далее</b></font> " ----> node_483
  node_484(["   🚀 ВЫЗОВ: completed()   " ])
  node_482 -- " <font color='black'><b>далее</b></font> " ----> node_484
  class node_484 func_style
  node_485["   📂 БЛОК КОДА { }   " ]
  node_481 -- " <font color='black'><b>далее</b></font> " ----> node_485
  node_486(["   🚀 ВЫЗОВ: print()   " ])
  node_485 -- " <font color='black'><b>далее</b></font> " ----> node_486
  class node_486 func_style
  node_487["   ⚙️ ОПЕРАЦИЯ    " ]
  node_486 -- " <font color='black'><b>далее</b></font> " ----> node_487
  class node_487 op_style
  node_488(["   🔍 task   " ])
  node_487 -- " <font color='black'><b>далее</b></font> " ----> node_488
  node_489(["   🚀 ВЫЗОВ: toString()   " ])
  node_487 -- " <font color='black'><b>далее</b></font> " ----> node_489
  class node_489 func_style
  node_490["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_485 -- " <font color='black'><b>далее</b></font> " ----> node_490
  class node_490 op_style
  node_491(["   🔍 count   " ])
  node_490 -- " <font color='black'><b>далее</b></font> " ----> node_491
  node_492["   ➕ СЛОЖИТЬ (+)    " ]
  node_490 -- " <font color='black'><b>далее</b></font> " ----> node_492
  class node_492 op_style
  node_493(["   🔍 count   " ])
  node_492 -- " <font color='black'><b>далее</b></font> " ----> node_493
  node_494["   💎 1   "]
  node_492 -- " <font color='black'><b>далее</b></font> " ----> node_494
  node_495{"   ❓ ЕСЛИ (if)   " }
  node_468 -- " <font color='black'><b>далее</b></font> " ----> node_495
  class node_495 logic_style
  node_496["   ⚖️ РАВНО (==)    " ]
  node_495 -- " <font color='black'><b>далее</b></font> " ----> node_496
  class node_496 op_style
  node_497(["   🔍 count   " ])
  node_496 -- " <font color='black'><b>далее</b></font> " ----> node_497
  node_498["   💎 0   "]
  node_496 -- " <font color='black'><b>далее</b></font> " ----> node_498
  node_499["   📂 БЛОК КОДА { }   " ]
  node_495 -- " <font color='black'><b>далее</b></font> " ----> node_499
  node_500(["   🚀 ВЫЗОВ: print()   " ])
  node_499 -- " <font color='black'><b>далее</b></font> " ----> node_500
  class node_500 func_style
  node_501["   💎 No completed tasks   "]
  node_500 -- " <font color='black'><b>далее</b></font> " ----> node_501
  node_502(["   🚀 ВЫЗОВ: print()   " ])
  node_468 -- " <font color='black'><b>далее</b></font> " ----> node_502
  class node_502 func_style
  node_503["   💎 =======================   "]
  node_502 -- " <font color='black'><b>далее</b></font> " ----> node_503
  node_504(["   🚀 ВЫЗОВ: print()   " ])
  node_468 -- " <font color='black'><b>далее</b></font> " ----> node_504
  class node_504 func_style
  node_505["   💎     "]
  node_504 -- " <font color='black'><b>далее</b></font> " ----> node_505
  node_506(("    public МЕТОД: completeTask   " ))
  node_182 -- " <font color='black'><b>член_класса</b></font> " ----> node_506
  class node_506 func_style
  node_507(("   🔨 ФУНКЦИЯ: completeTask
Вернет: auto   " ))
  node_506 -- " <font color='black'><b>далее</b></font> " ----> node_507
  class node_507 func_style
  node_508(["   АРГ: taskId (auto)   " ])
  node_507 -- " <font color='black'><b>сигнатура</b></font> " ----> node_508
  node_509["   📂 БЛОК КОДА { }   " ]
  node_507 -- " <font color='black'><b>далее</b></font> " ----> node_509
  node_510{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_509 -- " <font color='black'><b>далее</b></font> " ----> node_510
  class node_510 var_style
  node_511(["   ИМЯ: task
Тип: auto   " ])
  node_510 -- " <font color='black'><b>память</b></font> " ----> node_511
  node_512["   ⚙️ ОПЕРАЦИЯ    " ]
  node_511 -- " <font color='black'><b>далее</b></font> " ----> node_512
  class node_512 op_style
  node_513(["   🔍 this   " ])
  node_512 -- " <font color='black'><b>далее</b></font> " ----> node_513
  node_514(["   🚀 ВЫЗОВ: findTaskById()   " ])
  node_512 -- " <font color='black'><b>далее</b></font> " ----> node_514
  class node_514 func_style
  node_515(["   🔍 taskId   " ])
  node_514 -- " <font color='black'><b>далее</b></font> " ----> node_515
  node_516{"   ❓ ЕСЛИ (if)   " }
  node_509 -- " <font color='black'><b>далее</b></font> " ----> node_516
  class node_516 logic_style
  node_517["   ⚖️ РАВНО (==)    " ]
  node_516 -- " <font color='black'><b>далее</b></font> " ----> node_517
  class node_517 op_style
  node_518(["   🔍 task   " ])
  node_517 -- " <font color='black'><b>далее</b></font> " ----> node_518
  node_519["   💎 null   "]
  node_517 -- " <font color='black'><b>далее</b></font> " ----> node_519
  node_520["   📂 БЛОК КОДА { }   " ]
  node_516 -- " <font color='black'><b>далее</b></font> " ----> node_520
  node_521(["   🚀 ВЫЗОВ: print()   " ])
  node_520 -- " <font color='black'><b>далее</b></font> " ----> node_521
  class node_521 func_style
  node_522["   ➕ СЛОЖИТЬ (+)    " ]
  node_521 -- " <font color='black'><b>далее</b></font> " ----> node_522
  class node_522 op_style
  node_523["   ➕ СЛОЖИТЬ (+)    " ]
  node_522 -- " <font color='black'><b>далее</b></font> " ----> node_523
  class node_523 op_style
  node_524["   💎 Task    "]
  node_523 -- " <font color='black'><b>далее</b></font> " ----> node_524
  node_525(["   🔍 taskId   " ])
  node_523 -- " <font color='black'><b>далее</b></font> " ----> node_525
  node_526["   💎  not found   "]
  node_522 -- " <font color='black'><b>далее</b></font> " ----> node_526
  node_527[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_520 -- " <font color='black'><b>далее</b></font> " ----> node_527
  node_528["   💎 false   "]
  node_527 -- " <font color='black'><b>далее</b></font> " ----> node_528
  node_529{"   ❓ ЕСЛИ (if)   " }
  node_509 -- " <font color='black'><b>далее</b></font> " ----> node_529
  class node_529 logic_style
  node_530["   ⚙️ ОПЕРАЦИЯ    " ]
  node_529 -- " <font color='black'><b>далее</b></font> " ----> node_530
  class node_530 op_style
  node_531(["   🔍 task   " ])
  node_530 -- " <font color='black'><b>далее</b></font> " ----> node_531
  node_532(["   🚀 ВЫЗОВ: completed()   " ])
  node_530 -- " <font color='black'><b>далее</b></font> " ----> node_532
  class node_532 func_style
  node_533["   📂 БЛОК КОДА { }   " ]
  node_529 -- " <font color='black'><b>далее</b></font> " ----> node_533
  node_534(["   🚀 ВЫЗОВ: print()   " ])
  node_533 -- " <font color='black'><b>далее</b></font> " ----> node_534
  class node_534 func_style
  node_535["   ➕ СЛОЖИТЬ (+)    " ]
  node_534 -- " <font color='black'><b>далее</b></font> " ----> node_535
  class node_535 op_style
  node_536["   ➕ СЛОЖИТЬ (+)    " ]
  node_535 -- " <font color='black'><b>далее</b></font> " ----> node_536
  class node_536 op_style
  node_537["   💎 Task    "]
  node_536 -- " <font color='black'><b>далее</b></font> " ----> node_537
  node_538(["   🔍 taskId   " ])
  node_536 -- " <font color='black'><b>далее</b></font> " ----> node_538
  node_539["   💎  is already completed   "]
  node_535 -- " <font color='black'><b>далее</b></font> " ----> node_539
  node_540[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_533 -- " <font color='black'><b>далее</b></font> " ----> node_540
  node_541["   💎 false   "]
  node_540 -- " <font color='black'><b>далее</b></font> " ----> node_541
  node_542["   ⚙️ ОПЕРАЦИЯ    " ]
  node_509 -- " <font color='black'><b>далее</b></font> " ----> node_542
  class node_542 op_style
  node_543(["   🔍 task   " ])
  node_542 -- " <font color='black'><b>далее</b></font> " ----> node_543
  node_544(["   🚀 ВЫЗОВ: markComplete()   " ])
  node_542 -- " <font color='black'><b>далее</b></font> " ----> node_544
  class node_544 func_style
  node_545(["   🚀 ВЫЗОВ: print()   " ])
  node_509 -- " <font color='black'><b>далее</b></font> " ----> node_545
  class node_545 func_style
  node_546["   ➕ СЛОЖИТЬ (+)    " ]
  node_545 -- " <font color='black'><b>далее</b></font> " ----> node_546
  class node_546 op_style
  node_547["   💎 Task completed:    "]
  node_546 -- " <font color='black'><b>далее</b></font> " ----> node_547
  node_548["   ⚙️ ОПЕРАЦИЯ    " ]
  node_546 -- " <font color='black'><b>далее</b></font> " ----> node_548
  class node_548 op_style
  node_549(["   🔍 task   " ])
  node_548 -- " <font color='black'><b>далее</b></font> " ----> node_549
  node_550(["   🚀 ВЫЗОВ: title()   " ])
  node_548 -- " <font color='black'><b>далее</b></font> " ----> node_550
  class node_550 func_style
  node_551[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_509 -- " <font color='black'><b>далее</b></font> " ----> node_551
  node_552["   💎 true   "]
  node_551 -- " <font color='black'><b>далее</b></font> " ----> node_552
  node_553(("    public МЕТОД: uncompleteTask   " ))
  node_182 -- " <font color='black'><b>член_класса</b></font> " ----> node_553
  class node_553 func_style
  node_554(("   🔨 ФУНКЦИЯ: uncompleteTask
Вернет: auto   " ))
  node_553 -- " <font color='black'><b>далее</b></font> " ----> node_554
  class node_554 func_style
  node_555(["   АРГ: taskId (auto)   " ])
  node_554 -- " <font color='black'><b>сигнатура</b></font> " ----> node_555
  node_556["   📂 БЛОК КОДА { }   " ]
  node_554 -- " <font color='black'><b>далее</b></font> " ----> node_556
  node_557{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_556 -- " <font color='black'><b>далее</b></font> " ----> node_557
  class node_557 var_style
  node_558(["   ИМЯ: task
Тип: auto   " ])
  node_557 -- " <font color='black'><b>память</b></font> " ----> node_558
  node_559["   ⚙️ ОПЕРАЦИЯ    " ]
  node_558 -- " <font color='black'><b>далее</b></font> " ----> node_559
  class node_559 op_style
  node_560(["   🔍 this   " ])
  node_559 -- " <font color='black'><b>далее</b></font> " ----> node_560
  node_561(["   🚀 ВЫЗОВ: findTaskById()   " ])
  node_559 -- " <font color='black'><b>далее</b></font> " ----> node_561
  class node_561 func_style
  node_562(["   🔍 taskId   " ])
  node_561 -- " <font color='black'><b>далее</b></font> " ----> node_562
  node_563{"   ❓ ЕСЛИ (if)   " }
  node_556 -- " <font color='black'><b>далее</b></font> " ----> node_563
  class node_563 logic_style
  node_564["   ⚖️ РАВНО (==)    " ]
  node_563 -- " <font color='black'><b>далее</b></font> " ----> node_564
  class node_564 op_style
  node_565(["   🔍 task   " ])
  node_564 -- " <font color='black'><b>далее</b></font> " ----> node_565
  node_566["   💎 null   "]
  node_564 -- " <font color='black'><b>далее</b></font> " ----> node_566
  node_567["   📂 БЛОК КОДА { }   " ]
  node_563 -- " <font color='black'><b>далее</b></font> " ----> node_567
  node_568(["   🚀 ВЫЗОВ: print()   " ])
  node_567 -- " <font color='black'><b>далее</b></font> " ----> node_568
  class node_568 func_style
  node_569["   ➕ СЛОЖИТЬ (+)    " ]
  node_568 -- " <font color='black'><b>далее</b></font> " ----> node_569
  class node_569 op_style
  node_570["   ➕ СЛОЖИТЬ (+)    " ]
  node_569 -- " <font color='black'><b>далее</b></font> " ----> node_570
  class node_570 op_style
  node_571["   💎 Task    "]
  node_570 -- " <font color='black'><b>далее</b></font> " ----> node_571
  node_572(["   🔍 taskId   " ])
  node_570 -- " <font color='black'><b>далее</b></font> " ----> node_572
  node_573["   💎  not found   "]
  node_569 -- " <font color='black'><b>далее</b></font> " ----> node_573
  node_574[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_567 -- " <font color='black'><b>далее</b></font> " ----> node_574
  node_575["   💎 false   "]
  node_574 -- " <font color='black'><b>далее</b></font> " ----> node_575
  node_576{"   ❓ ЕСЛИ (if)   " }
  node_556 -- " <font color='black'><b>далее</b></font> " ----> node_576
  class node_576 logic_style
  node_577(["   ❗ ОТРИЦАНИЕ (!)    " ])
  node_576 -- " <font color='black'><b>далее</b></font> " ----> node_577
  class node_577 op_style
  node_578["   ⚙️ ОПЕРАЦИЯ    " ]
  node_577 -- " <font color='black'><b>далее</b></font> " ----> node_578
  class node_578 op_style
  node_579(["   🔍 task   " ])
  node_578 -- " <font color='black'><b>далее</b></font> " ----> node_579
  node_580(["   🚀 ВЫЗОВ: completed()   " ])
  node_578 -- " <font color='black'><b>далее</b></font> " ----> node_580
  class node_580 func_style
  node_581["   📂 БЛОК КОДА { }   " ]
  node_576 -- " <font color='black'><b>далее</b></font> " ----> node_581
  node_582(["   🚀 ВЫЗОВ: print()   " ])
  node_581 -- " <font color='black'><b>далее</b></font> " ----> node_582
  class node_582 func_style
  node_583["   ➕ СЛОЖИТЬ (+)    " ]
  node_582 -- " <font color='black'><b>далее</b></font> " ----> node_583
  class node_583 op_style
  node_584["   ➕ СЛОЖИТЬ (+)    " ]
  node_583 -- " <font color='black'><b>далее</b></font> " ----> node_584
  class node_584 op_style
  node_585["   💎 Task    "]
  node_584 -- " <font color='black'><b>далее</b></font> " ----> node_585
  node_586(["   🔍 taskId   " ])
  node_584 -- " <font color='black'><b>далее</b></font> " ----> node_586
  node_587["   💎  is not completed   "]
  node_583 -- " <font color='black'><b>далее</b></font> " ----> node_587
  node_588[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_581 -- " <font color='black'><b>далее</b></font> " ----> node_588
  node_589["   💎 false   "]
  node_588 -- " <font color='black'><b>далее</b></font> " ----> node_589
  node_590["   ⚙️ ОПЕРАЦИЯ    " ]
  node_556 -- " <font color='black'><b>далее</b></font> " ----> node_590
  class node_590 op_style
  node_591(["   🔍 task   " ])
  node_590 -- " <font color='black'><b>далее</b></font> " ----> node_591
  node_592(["   🚀 ВЫЗОВ: markIncomplete()   " ])
  node_590 -- " <font color='black'><b>далее</b></font> " ----> node_592
  class node_592 func_style
  node_593(["   🚀 ВЫЗОВ: print()   " ])
  node_556 -- " <font color='black'><b>далее</b></font> " ----> node_593
  class node_593 func_style
  node_594["   ➕ СЛОЖИТЬ (+)    " ]
  node_593 -- " <font color='black'><b>далее</b></font> " ----> node_594
  class node_594 op_style
  node_595["   💎 Task reopened:    "]
  node_594 -- " <font color='black'><b>далее</b></font> " ----> node_595
  node_596["   ⚙️ ОПЕРАЦИЯ    " ]
  node_594 -- " <font color='black'><b>далее</b></font> " ----> node_596
  class node_596 op_style
  node_597(["   🔍 task   " ])
  node_596 -- " <font color='black'><b>далее</b></font> " ----> node_597
  node_598(["   🚀 ВЫЗОВ: title()   " ])
  node_596 -- " <font color='black'><b>далее</b></font> " ----> node_598
  class node_598 func_style
  node_599[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_556 -- " <font color='black'><b>далее</b></font> " ----> node_599
  node_600["   💎 true   "]
  node_599 -- " <font color='black'><b>далее</b></font> " ----> node_600
  node_601(("    public МЕТОД: getStats   " ))
  node_182 -- " <font color='black'><b>член_класса</b></font> " ----> node_601
  class node_601 func_style
  node_602(("   🔨 ФУНКЦИЯ: getStats
Вернет: auto   " ))
  node_601 -- " <font color='black'><b>далее</b></font> " ----> node_602
  class node_602 func_style
  node_603["   📂 БЛОК КОДА { }   " ]
  node_602 -- " <font color='black'><b>далее</b></font> " ----> node_603
  node_604{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_603 -- " <font color='black'><b>далее</b></font> " ----> node_604
  class node_604 var_style
  node_605(["   ИМЯ: total
Тип: auto   " ])
  node_604 -- " <font color='black'><b>память</b></font> " ----> node_605
  node_606(["   🚀 ВЫЗОВ: len()   " ])
  node_605 -- " <font color='black'><b>далее</b></font> " ----> node_606
  class node_606 func_style
  node_607["   ⚙️ ОПЕРАЦИЯ    " ]
  node_606 -- " <font color='black'><b>далее</b></font> " ----> node_607
  class node_607 op_style
  node_608(["   🔍 this   " ])
  node_607 -- " <font color='black'><b>далее</b></font> " ----> node_608
  node_609(["   🔍 tasks   " ])
  node_607 -- " <font color='black'><b>далее</b></font> " ----> node_609
  node_610{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_603 -- " <font color='black'><b>далее</b></font> " ----> node_610
  class node_610 var_style
  node_611(["   ИМЯ: completed
Тип: auto   " ])
  node_610 -- " <font color='black'><b>память</b></font> " ----> node_611
  node_612["   💎 0   "]
  node_611 -- " <font color='black'><b>далее</b></font> " ----> node_612
  node_613{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_603 -- " <font color='black'><b>далее</b></font> " ----> node_613
  class node_613 var_style
  node_614(["   ИМЯ: highPriority
Тип: auto   " ])
  node_613 -- " <font color='black'><b>память</b></font> " ----> node_614
  node_615["   💎 0   "]
  node_614 -- " <font color='black'><b>далее</b></font> " ----> node_615
  node_616{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_603 -- " <font color='black'><b>далее</b></font> " ----> node_616
  class node_616 var_style
  node_617(["   ИМЯ: mediumPriority
Тип: auto   " ])
  node_616 -- " <font color='black'><b>память</b></font> " ----> node_617
  node_618["   💎 0   "]
  node_617 -- " <font color='black'><b>далее</b></font> " ----> node_618
  node_619{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_603 -- " <font color='black'><b>далее</b></font> " ----> node_619
  class node_619 var_style
  node_620(["   ИМЯ: lowPriority
Тип: auto   " ])
  node_619 -- " <font color='black'><b>память</b></font> " ----> node_620
  node_621["   💎 0   "]
  node_620 -- " <font color='black'><b>далее</b></font> " ----> node_621
  node_622{{"   ♻️ ЦИКЛ: for (task)   " }}
  node_603 -- " <font color='black'><b>далее</b></font> " ----> node_622
  class node_622 logic_style
  node_623["   ⚙️ ОПЕРАЦИЯ    " ]
  node_622 -- " <font color='black'><b>далее</b></font> " ----> node_623
  class node_623 op_style
  node_624(["   🔍 this   " ])
  node_623 -- " <font color='black'><b>далее</b></font> " ----> node_624
  node_625(["   🔍 tasks   " ])
  node_623 -- " <font color='black'><b>далее</b></font> " ----> node_625
  node_626["   📂 БЛОК КОДА { }   " ]
  node_622 -- " <font color='black'><b>далее</b></font> " ----> node_626
  node_627{"   ❓ ЕСЛИ (if)   " }
  node_626 -- " <font color='black'><b>далее</b></font> " ----> node_627
  class node_627 logic_style
  node_628["   ⚙️ ОПЕРАЦИЯ    " ]
  node_627 -- " <font color='black'><b>далее</b></font> " ----> node_628
  class node_628 op_style
  node_629(["   🔍 task   " ])
  node_628 -- " <font color='black'><b>далее</b></font> " ----> node_629
  node_630(["   🚀 ВЫЗОВ: completed()   " ])
  node_628 -- " <font color='black'><b>далее</b></font> " ----> node_630
  class node_630 func_style
  node_631["   📂 БЛОК КОДА { }   " ]
  node_627 -- " <font color='black'><b>далее</b></font> " ----> node_631
  node_632["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_631 -- " <font color='black'><b>далее</b></font> " ----> node_632
  class node_632 op_style
  node_633(["   🔍 completed   " ])
  node_632 -- " <font color='black'><b>далее</b></font> " ----> node_633
  node_634["   ➕ СЛОЖИТЬ (+)    " ]
  node_632 -- " <font color='black'><b>далее</b></font> " ----> node_634
  class node_634 op_style
  node_635(["   🔍 completed   " ])
  node_634 -- " <font color='black'><b>далее</b></font> " ----> node_635
  node_636["   💎 1   "]
  node_634 -- " <font color='black'><b>далее</b></font> " ----> node_636
  node_637{"   ❓ ЕСЛИ (if)   " }
  node_626 -- " <font color='black'><b>далее</b></font> " ----> node_637
  class node_637 logic_style
  node_638["   ⚖️ РАВНО (==)    " ]
  node_637 -- " <font color='black'><b>далее</b></font> " ----> node_638
  class node_638 op_style
  node_639["   ⚙️ ОПЕРАЦИЯ    " ]
  node_638 -- " <font color='black'><b>далее</b></font> " ----> node_639
  class node_639 op_style
  node_640(["   🔍 task   " ])
  node_639 -- " <font color='black'><b>далее</b></font> " ----> node_640
  node_641(["   🚀 ВЫЗОВ: priority()   " ])
  node_639 -- " <font color='black'><b>далее</b></font> " ----> node_641
  class node_641 func_style
  node_642["   💎 1   "]
  node_638 -- " <font color='black'><b>далее</b></font> " ----> node_642
  node_643["   📂 БЛОК КОДА { }   " ]
  node_637 -- " <font color='black'><b>далее</b></font> " ----> node_643
  node_644["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_643 -- " <font color='black'><b>далее</b></font> " ----> node_644
  class node_644 op_style
  node_645(["   🔍 highPriority   " ])
  node_644 -- " <font color='black'><b>далее</b></font> " ----> node_645
  node_646["   ➕ СЛОЖИТЬ (+)    " ]
  node_644 -- " <font color='black'><b>далее</b></font> " ----> node_646
  class node_646 op_style
  node_647(["   🔍 highPriority   " ])
  node_646 -- " <font color='black'><b>далее</b></font> " ----> node_647
  node_648["   💎 1   "]
  node_646 -- " <font color='black'><b>далее</b></font> " ----> node_648
  node_649{"   ❓ ЕСЛИ (if)   " }
  node_637 -- " <font color='black'><b>далее</b></font> " ----> node_649
  class node_649 logic_style
  node_650["   ⚖️ РАВНО (==)    " ]
  node_649 -- " <font color='black'><b>далее</b></font> " ----> node_650
  class node_650 op_style
  node_651["   ⚙️ ОПЕРАЦИЯ    " ]
  node_650 -- " <font color='black'><b>далее</b></font> " ----> node_651
  class node_651 op_style
  node_652(["   🔍 task   " ])
  node_651 -- " <font color='black'><b>далее</b></font> " ----> node_652
  node_653(["   🚀 ВЫЗОВ: priority()   " ])
  node_651 -- " <font color='black'><b>далее</b></font> " ----> node_653
  class node_653 func_style
  node_654["   💎 2   "]
  node_650 -- " <font color='black'><b>далее</b></font> " ----> node_654
  node_655["   📂 БЛОК КОДА { }   " ]
  node_649 -- " <font color='black'><b>далее</b></font> " ----> node_655
  node_656["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_655 -- " <font color='black'><b>далее</b></font> " ----> node_656
  class node_656 op_style
  node_657(["   🔍 mediumPriority   " ])
  node_656 -- " <font color='black'><b>далее</b></font> " ----> node_657
  node_658["   ➕ СЛОЖИТЬ (+)    " ]
  node_656 -- " <font color='black'><b>далее</b></font> " ----> node_658
  class node_658 op_style
  node_659(["   🔍 mediumPriority   " ])
  node_658 -- " <font color='black'><b>далее</b></font> " ----> node_659
  node_660["   💎 1   "]
  node_658 -- " <font color='black'><b>далее</b></font> " ----> node_660
  node_661["   📂 БЛОК КОДА { }   " ]
  node_649 -- " <font color='black'><b>далее</b></font> " ----> node_661
  node_662["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_661 -- " <font color='black'><b>далее</b></font> " ----> node_662
  class node_662 op_style
  node_663(["   🔍 lowPriority   " ])
  node_662 -- " <font color='black'><b>далее</b></font> " ----> node_663
  node_664["   ➕ СЛОЖИТЬ (+)    " ]
  node_662 -- " <font color='black'><b>далее</b></font> " ----> node_664
  class node_664 op_style
  node_665(["   🔍 lowPriority   " ])
  node_664 -- " <font color='black'><b>далее</b></font> " ----> node_665
  node_666["   💎 1   "]
  node_664 -- " <font color='black'><b>далее</b></font> " ----> node_666
  node_667(["   🚀 ВЫЗОВ: print()   " ])
  node_603 -- " <font color='black'><b>далее</b></font> " ----> node_667
  class node_667 func_style
  node_668["   💎     "]
  node_667 -- " <font color='black'><b>далее</b></font> " ----> node_668
  node_669(["   🚀 ВЫЗОВ: print()   " ])
  node_603 -- " <font color='black'><b>далее</b></font> " ----> node_669
  class node_669 func_style
  node_670["   ➕ СЛОЖИТЬ (+)    " ]
  node_669 -- " <font color='black'><b>далее</b></font> " ----> node_670
  class node_670 op_style
  node_671["   ➕ СЛОЖИТЬ (+)    " ]
  node_670 -- " <font color='black'><b>далее</b></font> " ----> node_671
  class node_671 op_style
  node_672["   💎 === Statistics for    "]
  node_671 -- " <font color='black'><b>далее</b></font> " ----> node_672
  node_673["   ⚙️ ОПЕРАЦИЯ    " ]
  node_671 -- " <font color='black'><b>далее</b></font> " ----> node_673
  class node_673 op_style
  node_674(["   🔍 this   " ])
  node_673 -- " <font color='black'><b>далее</b></font> " ----> node_674
  node_675(["   🔍 name   " ])
  node_673 -- " <font color='black'><b>далее</b></font> " ----> node_675
  node_676["   💎  ===   "]
  node_670 -- " <font color='black'><b>далее</b></font> " ----> node_676
  node_677(["   🚀 ВЫЗОВ: print()   " ])
  node_603 -- " <font color='black'><b>далее</b></font> " ----> node_677
  class node_677 func_style
  node_678["   ➕ СЛОЖИТЬ (+)    " ]
  node_677 -- " <font color='black'><b>далее</b></font> " ----> node_678
  class node_678 op_style
  node_679["   💎 Total tasks:    "]
  node_678 -- " <font color='black'><b>далее</b></font> " ----> node_679
  node_680(["   🔍 total   " ])
  node_678 -- " <font color='black'><b>далее</b></font> " ----> node_680
  node_681(["   🚀 ВЫЗОВ: print()   " ])
  node_603 -- " <font color='black'><b>далее</b></font> " ----> node_681
  class node_681 func_style
  node_682["   ➕ СЛОЖИТЬ (+)    " ]
  node_681 -- " <font color='black'><b>далее</b></font> " ----> node_682
  class node_682 op_style
  node_683["   💎 Completed:    "]
  node_682 -- " <font color='black'><b>далее</b></font> " ----> node_683
  node_684(["   🔍 completed   " ])
  node_682 -- " <font color='black'><b>далее</b></font> " ----> node_684
  node_685(["   🚀 ВЫЗОВ: print()   " ])
  node_603 -- " <font color='black'><b>далее</b></font> " ----> node_685
  class node_685 func_style
  node_686["   ➕ СЛОЖИТЬ (+)    " ]
  node_685 -- " <font color='black'><b>далее</b></font> " ----> node_686
  class node_686 op_style
  node_687["   💎 Pending:    "]
  node_686 -- " <font color='black'><b>далее</b></font> " ----> node_687
  node_688["   ➖ ВЫЧЕСТЬ (-)    " ]
  node_686 -- " <font color='black'><b>далее</b></font> " ----> node_688
  class node_688 op_style
  node_689(["   🔍 total   " ])
  node_688 -- " <font color='black'><b>далее</b></font> " ----> node_689
  node_690(["   🔍 completed   " ])
  node_688 -- " <font color='black'><b>далее</b></font> " ----> node_690
  node_691(["   🚀 ВЫЗОВ: print()   " ])
  node_603 -- " <font color='black'><b>далее</b></font> " ----> node_691
  class node_691 func_style
  node_692["   ➕ СЛОЖИТЬ (+)    " ]
  node_691 -- " <font color='black'><b>далее</b></font> " ----> node_692
  class node_692 op_style
  node_693["   ➕ СЛОЖИТЬ (+)    " ]
  node_692 -- " <font color='black'><b>далее</b></font> " ----> node_693
  class node_693 op_style
  node_694["   💎 Completion rate:    "]
  node_693 -- " <font color='black'><b>далее</b></font> " ----> node_694
  node_695["   ➗ РАЗДЕЛИТЬ (/)    " ]
  node_693 -- " <font color='black'><b>далее</b></font> " ----> node_695
  class node_695 op_style
  node_696["   ✖️ УМНОЖИТЬ (*)    " ]
  node_695 -- " <font color='black'><b>далее</b></font> " ----> node_696
  class node_696 op_style
  node_697(["   🔍 completed   " ])
  node_696 -- " <font color='black'><b>далее</b></font> " ----> node_697
  node_698["   💎 100   "]
  node_696 -- " <font color='black'><b>далее</b></font> " ----> node_698
  node_699(["   🔍 total   " ])
  node_695 -- " <font color='black'><b>далее</b></font> " ----> node_699
  node_700["   💎  percent   "]
  node_692 -- " <font color='black'><b>далее</b></font> " ----> node_700
  node_701(["   🚀 ВЫЗОВ: print()   " ])
  node_603 -- " <font color='black'><b>далее</b></font> " ----> node_701
  class node_701 func_style
  node_702["   💎     "]
  node_701 -- " <font color='black'><b>далее</b></font> " ----> node_702
  node_703(["   🚀 ВЫЗОВ: print()   " ])
  node_603 -- " <font color='black'><b>далее</b></font> " ----> node_703
  class node_703 func_style
  node_704["   💎 By priority:   "]
  node_703 -- " <font color='black'><b>далее</b></font> " ----> node_704
  node_705(["   🚀 ВЫЗОВ: print()   " ])
  node_603 -- " <font color='black'><b>далее</b></font> " ----> node_705
  class node_705 func_style
  node_706["   ➕ СЛОЖИТЬ (+)    " ]
  node_705 -- " <font color='black'><b>далее</b></font> " ----> node_706
  class node_706 op_style
  node_707["   💎   High:    "]
  node_706 -- " <font color='black'><b>далее</b></font> " ----> node_707
  node_708(["   🔍 highPriority   " ])
  node_706 -- " <font color='black'><b>далее</b></font> " ----> node_708
  node_709(["   🚀 ВЫЗОВ: print()   " ])
  node_603 -- " <font color='black'><b>далее</b></font> " ----> node_709
  class node_709 func_style
  node_710["   ➕ СЛОЖИТЬ (+)    " ]
  node_709 -- " <font color='black'><b>далее</b></font> " ----> node_710
  class node_710 op_style
  node_711["   💎   Medium:    "]
  node_710 -- " <font color='black'><b>далее</b></font> " ----> node_711
  node_712(["   🔍 mediumPriority   " ])
  node_710 -- " <font color='black'><b>далее</b></font> " ----> node_712
  node_713(["   🚀 ВЫЗОВ: print()   " ])
  node_603 -- " <font color='black'><b>далее</b></font> " ----> node_713
  class node_713 func_style
  node_714["   ➕ СЛОЖИТЬ (+)    " ]
  node_713 -- " <font color='black'><b>далее</b></font> " ----> node_714
  class node_714 op_style
  node_715["   💎   Low:    "]
  node_714 -- " <font color='black'><b>далее</b></font> " ----> node_715
  node_716(["   🔍 lowPriority   " ])
  node_714 -- " <font color='black'><b>далее</b></font> " ----> node_716
  node_717(["   🚀 ВЫЗОВ: print()   " ])
  node_603 -- " <font color='black'><b>далее</b></font> " ----> node_717
  class node_717 func_style
  node_718["   💎 ===================================   "]
  node_717 -- " <font color='black'><b>далее</b></font> " ----> node_718
  node_719(["   🚀 ВЫЗОВ: print()   " ])
  node_603 -- " <font color='black'><b>далее</b></font> " ----> node_719
  class node_719 func_style
  node_720["   💎     "]
  node_719 -- " <font color='black'><b>далее</b></font> " ----> node_720
  node_721(("   🔨 ФУНКЦИЯ: getCurrentTime
Вернет: auto   " ))
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_721
  class node_721 func_style
  node_722["   📂 БЛОК КОДА { }   " ]
  node_721 -- " <font color='black'><b>далее</b></font> " ----> node_722
  node_723[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_722 -- " <font color='black'><b>далее</b></font> " ----> node_723
  node_724["   💎 2024-01-01 00:00:00   "]
  node_723 -- " <font color='black'><b>далее</b></font> " ----> node_724
  node_725(("   🔨 ФУНКЦИЯ: showMenu
Вернет: auto   " ))
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_725
  class node_725 func_style
  node_726["   📂 БЛОК КОДА { }   " ]
  node_725 -- " <font color='black'><b>далее</b></font> " ----> node_726
  node_727(["   🚀 ВЫЗОВ: print()   " ])
  node_726 -- " <font color='black'><b>далее</b></font> " ----> node_727
  class node_727 func_style
  node_728["   💎     "]
  node_727 -- " <font color='black'><b>далее</b></font> " ----> node_728
  node_729(["   🚀 ВЫЗОВ: print()   " ])
  node_726 -- " <font color='black'><b>далее</b></font> " ----> node_729
  class node_729 func_style
  node_730["   💎 === TODO LIST MANAGER ===   "]
  node_729 -- " <font color='black'><b>далее</b></font> " ----> node_730
  node_731(["   🚀 ВЫЗОВ: print()   " ])
  node_726 -- " <font color='black'><b>далее</b></font> " ----> node_731
  class node_731 func_style
  node_732["   💎 1. Add task   "]
  node_731 -- " <font color='black'><b>далее</b></font> " ----> node_732
  node_733(["   🚀 ВЫЗОВ: print()   " ])
  node_726 -- " <font color='black'><b>далее</b></font> " ----> node_733
  class node_733 func_style
  node_734["   💎 2. List all tasks   "]
  node_733 -- " <font color='black'><b>далее</b></font> " ----> node_734
  node_735(["   🚀 ВЫЗОВ: print()   " ])
  node_726 -- " <font color='black'><b>далее</b></font> " ----> node_735
  class node_735 func_style
  node_736["   💎 3. List pending tasks   "]
  node_735 -- " <font color='black'><b>далее</b></font> " ----> node_736
  node_737(["   🚀 ВЫЗОВ: print()   " ])
  node_726 -- " <font color='black'><b>далее</b></font> " ----> node_737
  class node_737 func_style
  node_738["   💎 4. List completed tasks   "]
  node_737 -- " <font color='black'><b>далее</b></font> " ----> node_738
  node_739(["   🚀 ВЫЗОВ: print()   " ])
  node_726 -- " <font color='black'><b>далее</b></font> " ----> node_739
  class node_739 func_style
  node_740["   💎 5. Complete a task   "]
  node_739 -- " <font color='black'><b>далее</b></font> " ----> node_740
  node_741(["   🚀 ВЫЗОВ: print()   " ])
  node_726 -- " <font color='black'><b>далее</b></font> " ----> node_741
  class node_741 func_style
  node_742["   💎 6. Reopen a task   "]
  node_741 -- " <font color='black'><b>далее</b></font> " ----> node_742
  node_743(["   🚀 ВЫЗОВ: print()   " ])
  node_726 -- " <font color='black'><b>далее</b></font> " ----> node_743
  class node_743 func_style
  node_744["   💎 7. Remove a task   "]
  node_743 -- " <font color='black'><b>далее</b></font> " ----> node_744
  node_745(["   🚀 ВЫЗОВ: print()   " ])
  node_726 -- " <font color='black'><b>далее</b></font> " ----> node_745
  class node_745 func_style
  node_746["   💎 8. Show statistics   "]
  node_745 -- " <font color='black'><b>далее</b></font> " ----> node_746
  node_747(["   🚀 ВЫЗОВ: print()   " ])
  node_726 -- " <font color='black'><b>далее</b></font> " ----> node_747
  class node_747 func_style
  node_748["   💎 9. Find tasks by priority   "]
  node_747 -- " <font color='black'><b>далее</b></font> " ----> node_748
  node_749(["   🚀 ВЫЗОВ: print()   " ])
  node_726 -- " <font color='black'><b>далее</b></font> " ----> node_749
  class node_749 func_style
  node_750["   💎 10. Exit   "]
  node_749 -- " <font color='black'><b>далее</b></font> " ----> node_750
  node_751(["   🚀 ВЫЗОВ: print()   " ])
  node_726 -- " <font color='black'><b>далее</b></font> " ----> node_751
  class node_751 func_style
  node_752["   💎 =========================   "]
  node_751 -- " <font color='black'><b>далее</b></font> " ----> node_752
  node_753(["   🚀 ВЫЗОВ: print()   " ])
  node_726 -- " <font color='black'><b>далее</b></font> " ----> node_753
  class node_753 func_style
  node_754["   💎     "]
  node_753 -- " <font color='black'><b>далее</b></font> " ----> node_754
  node_755(("   🔨 ФУНКЦИЯ: main
Вернет: auto   " ))
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_755
  class node_755 func_style
  node_756["   📂 БЛОК КОДА { }   " ]
  node_755 -- " <font color='black'><b>далее</b></font> " ----> node_756
  node_757(["   🚀 ВЫЗОВ: print()   " ])
  node_756 -- " <font color='black'><b>далее</b></font> " ----> node_757
  class node_757 func_style
  node_758["   💎 Welcome to TODO List Manager!   "]
  node_757 -- " <font color='black'><b>далее</b></font> " ----> node_758
  node_759(["   🚀 ВЫЗОВ: print()   " ])
  node_756 -- " <font color='black'><b>далее</b></font> " ----> node_759
  class node_759 func_style
  node_760["   💎     "]
  node_759 -- " <font color='black'><b>далее</b></font> " ----> node_760
  node_761{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_756 -- " <font color='black'><b>далее</b></font> " ----> node_761
  class node_761 var_style
  node_762(["   ИМЯ: currentUser
Тип: auto   " ])
  node_761 -- " <font color='black'><b>память</b></font> " ----> node_762
  node_763(["   🚀 ВЫЗОВ: User()   " ])
  node_762 -- " <font color='black'><b>далее</b></font> " ----> node_763
  class node_763 func_style
  node_764["   💎 1   "]
  node_763 -- " <font color='black'><b>далее</b></font> " ----> node_764
  node_765["   💎 John Doe   "]
  node_763 -- " <font color='black'><b>далее</b></font> " ----> node_765
  node_766{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_756 -- " <font color='black'><b>далее</b></font> " ----> node_766
  class node_766 var_style
  node_767(["   ИМЯ: running
Тип: auto   " ])
  node_766 -- " <font color='black'><b>память</b></font> " ----> node_767
  node_768["   💎 true   "]
  node_767 -- " <font color='black'><b>далее</b></font> " ----> node_768
  node_769{{"   🔄 ЦИКЛ: while   " }}
  node_756 -- " <font color='black'><b>далее</b></font> " ----> node_769
  class node_769 logic_style
  node_770(["   🔍 running   " ])
  node_769 -- " <font color='black'><b>далее</b></font> " ----> node_770
  node_771["   📂 БЛОК КОДА { }   " ]
  node_769 -- " <font color='black'><b>далее</b></font> " ----> node_771
  node_772(["   🚀 ВЫЗОВ: showMenu()   " ])
  node_771 -- " <font color='black'><b>далее</b></font> " ----> node_772
  class node_772 func_style
  node_773{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_771 -- " <font color='black'><b>далее</b></font> " ----> node_773
  class node_773 var_style
  node_774(["   ИМЯ: choice
Тип: auto   " ])
  node_773 -- " <font color='black'><b>память</b></font> " ----> node_774
  node_775(["   🚀 ВЫЗОВ: input()   " ])
  node_774 -- " <font color='black'><b>далее</b></font> " ----> node_775
  class node_775 func_style
  node_776["   💎 Enter your choice:    "]
  node_775 -- " <font color='black'><b>далее</b></font> " ----> node_776
  node_777{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_771 -- " <font color='black'><b>далее</b></font> " ----> node_777
  class node_777 var_style
  node_778(["   ИМЯ: intChoice
Тип: auto   " ])
  node_777 -- " <font color='black'><b>память</b></font> " ----> node_778
  node_779(["   🚀 ВЫЗОВ: int()   " ])
  node_778 -- " <font color='black'><b>далее</b></font> " ----> node_779
  class node_779 func_style
  node_780(["   🔍 choice   " ])
  node_779 -- " <font color='black'><b>далее</b></font> " ----> node_780
  node_781{"   ❓ ЕСЛИ (if)   " }
  node_771 -- " <font color='black'><b>далее</b></font> " ----> node_781
  class node_781 logic_style
  node_782["   ⚖️ РАВНО (==)    " ]
  node_781 -- " <font color='black'><b>далее</b></font> " ----> node_782
  class node_782 op_style
  node_783(["   🔍 intChoice   " ])
  node_782 -- " <font color='black'><b>далее</b></font> " ----> node_783
  node_784["   💎 1   "]
  node_782 -- " <font color='black'><b>далее</b></font> " ----> node_784
  node_785["   📂 БЛОК КОДА { }   " ]
  node_781 -- " <font color='black'><b>далее</b></font> " ----> node_785
  node_786{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_785 -- " <font color='black'><b>далее</b></font> " ----> node_786
  class node_786 var_style
  node_787(["   ИМЯ: title
Тип: auto   " ])
  node_786 -- " <font color='black'><b>память</b></font> " ----> node_787
  node_788(["   🚀 ВЫЗОВ: input()   " ])
  node_787 -- " <font color='black'><b>далее</b></font> " ----> node_788
  class node_788 func_style
  node_789["   💎 Enter task title:    "]
  node_788 -- " <font color='black'><b>далее</b></font> " ----> node_789
  node_790{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_785 -- " <font color='black'><b>далее</b></font> " ----> node_790
  class node_790 var_style
  node_791(["   ИМЯ: description
Тип: auto   " ])
  node_790 -- " <font color='black'><b>память</b></font> " ----> node_791
  node_792(["   🚀 ВЫЗОВ: input()   " ])
  node_791 -- " <font color='black'><b>далее</b></font> " ----> node_792
  class node_792 func_style
  node_793["   💎 Enter description:    "]
  node_792 -- " <font color='black'><b>далее</b></font> " ----> node_793
  node_794{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_785 -- " <font color='black'><b>далее</b></font> " ----> node_794
  class node_794 var_style
  node_795(["   ИМЯ: priorityInput
Тип: auto   " ])
  node_794 -- " <font color='black'><b>память</b></font> " ----> node_795
  node_796(["   🚀 ВЫЗОВ: input()   " ])
  node_795 -- " <font color='black'><b>далее</b></font> " ----> node_796
  class node_796 func_style
  node_797["   💎 Enter priority (1=High, 2=Medium, 3=Low):    "]
  node_796 -- " <font color='black'><b>далее</b></font> " ----> node_797
  node_798{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_785 -- " <font color='black'><b>далее</b></font> " ----> node_798
  class node_798 var_style
  node_799(["   ИМЯ: priority
Тип: auto   " ])
  node_798 -- " <font color='black'><b>память</b></font> " ----> node_799
  node_800(["   🚀 ВЫЗОВ: int()   " ])
  node_799 -- " <font color='black'><b>далее</b></font> " ----> node_800
  class node_800 func_style
  node_801(["   🔍 priorityInput   " ])
  node_800 -- " <font color='black'><b>далее</b></font> " ----> node_801
  node_802{"   ❓ ЕСЛИ (if)   " }
  node_785 -- " <font color='black'><b>далее</b></font> " ----> node_802
  class node_802 logic_style
  node_803["   🧠 ЛОГИЧ. ИЛИ (|)    " ]
  node_802 -- " <font color='black'><b>далее</b></font> " ----> node_803
  class node_803 op_style
  node_804["   📉 МЕНЬШЕ (<)    " ]
  node_803 -- " <font color='black'><b>далее</b></font> " ----> node_804
  class node_804 op_style
  node_805(["   🔍 priority   " ])
  node_804 -- " <font color='black'><b>далее</b></font> " ----> node_805
  node_806["   💎 1   "]
  node_804 -- " <font color='black'><b>далее</b></font> " ----> node_806
  node_807["   📈 БОЛЬШЕ (>)    " ]
  node_803 -- " <font color='black'><b>далее</b></font> " ----> node_807
  class node_807 op_style
  node_808(["   🔍 priority   " ])
  node_807 -- " <font color='black'><b>далее</b></font> " ----> node_808
  node_809["   💎 3   "]
  node_807 -- " <font color='black'><b>далее</b></font> " ----> node_809
  node_810["   📂 БЛОК КОДА { }   " ]
  node_802 -- " <font color='black'><b>далее</b></font> " ----> node_810
  node_811(["   🚀 ВЫЗОВ: print()   " ])
  node_810 -- " <font color='black'><b>далее</b></font> " ----> node_811
  class node_811 func_style
  node_812["   💎 Invalid priority. Using Medium.   "]
  node_811 -- " <font color='black'><b>далее</b></font> " ----> node_812
  node_813["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_810 -- " <font color='black'><b>далее</b></font> " ----> node_813
  class node_813 op_style
  node_814(["   🔍 priority   " ])
  node_813 -- " <font color='black'><b>далее</b></font> " ----> node_814
  node_815["   💎 2   "]
  node_813 -- " <font color='black'><b>далее</b></font> " ----> node_815
  node_816["   ⚙️ ОПЕРАЦИЯ    " ]
  node_785 -- " <font color='black'><b>далее</b></font> " ----> node_816
  class node_816 op_style
  node_817(["   🔍 currentUser   " ])
  node_816 -- " <font color='black'><b>далее</b></font> " ----> node_817
  node_818(["   🚀 ВЫЗОВ: addTask()   " ])
  node_816 -- " <font color='black'><b>далее</b></font> " ----> node_818
  class node_818 func_style
  node_819(["   🔍 title   " ])
  node_818 -- " <font color='black'><b>далее</b></font> " ----> node_819
  node_820(["   🔍 description   " ])
  node_818 -- " <font color='black'><b>далее</b></font> " ----> node_820
  node_821(["   🔍 priority   " ])
  node_818 -- " <font color='black'><b>далее</b></font> " ----> node_821
  node_822{"   ❓ ЕСЛИ (if)   " }
  node_781 -- " <font color='black'><b>далее</b></font> " ----> node_822
  class node_822 logic_style
  node_823["   ⚖️ РАВНО (==)    " ]
  node_822 -- " <font color='black'><b>далее</b></font> " ----> node_823
  class node_823 op_style
  node_824(["   🔍 intChoice   " ])
  node_823 -- " <font color='black'><b>далее</b></font> " ----> node_824
  node_825["   💎 2   "]
  node_823 -- " <font color='black'><b>далее</b></font> " ----> node_825
  node_826["   📂 БЛОК КОДА { }   " ]
  node_822 -- " <font color='black'><b>далее</b></font> " ----> node_826
  node_827["   ⚙️ ОПЕРАЦИЯ    " ]
  node_826 -- " <font color='black'><b>далее</b></font> " ----> node_827
  class node_827 op_style
  node_828(["   🔍 currentUser   " ])
  node_827 -- " <font color='black'><b>далее</b></font> " ----> node_828
  node_829(["   🚀 ВЫЗОВ: listAllTasks()   " ])
  node_827 -- " <font color='black'><b>далее</b></font> " ----> node_829
  class node_829 func_style
  node_830{"   ❓ ЕСЛИ (if)   " }
  node_822 -- " <font color='black'><b>далее</b></font> " ----> node_830
  class node_830 logic_style
  node_831["   ⚖️ РАВНО (==)    " ]
  node_830 -- " <font color='black'><b>далее</b></font> " ----> node_831
  class node_831 op_style
  node_832(["   🔍 intChoice   " ])
  node_831 -- " <font color='black'><b>далее</b></font> " ----> node_832
  node_833["   💎 3   "]
  node_831 -- " <font color='black'><b>далее</b></font> " ----> node_833
  node_834["   📂 БЛОК КОДА { }   " ]
  node_830 -- " <font color='black'><b>далее</b></font> " ----> node_834
  node_835["   ⚙️ ОПЕРАЦИЯ    " ]
  node_834 -- " <font color='black'><b>далее</b></font> " ----> node_835
  class node_835 op_style
  node_836(["   🔍 currentUser   " ])
  node_835 -- " <font color='black'><b>далее</b></font> " ----> node_836
  node_837(["   🚀 ВЫЗОВ: listPendingTasks()   " ])
  node_835 -- " <font color='black'><b>далее</b></font> " ----> node_837
  class node_837 func_style
  node_838{"   ❓ ЕСЛИ (if)   " }
  node_830 -- " <font color='black'><b>далее</b></font> " ----> node_838
  class node_838 logic_style
  node_839["   ⚖️ РАВНО (==)    " ]
  node_838 -- " <font color='black'><b>далее</b></font> " ----> node_839
  class node_839 op_style
  node_840(["   🔍 intChoice   " ])
  node_839 -- " <font color='black'><b>далее</b></font> " ----> node_840
  node_841["   💎 4   "]
  node_839 -- " <font color='black'><b>далее</b></font> " ----> node_841
  node_842["   📂 БЛОК КОДА { }   " ]
  node_838 -- " <font color='black'><b>далее</b></font> " ----> node_842
  node_843["   ⚙️ ОПЕРАЦИЯ    " ]
  node_842 -- " <font color='black'><b>далее</b></font> " ----> node_843
  class node_843 op_style
  node_844(["   🔍 currentUser   " ])
  node_843 -- " <font color='black'><b>далее</b></font> " ----> node_844
  node_845(["   🚀 ВЫЗОВ: listCompletedTasks()   " ])
  node_843 -- " <font color='black'><b>далее</b></font> " ----> node_845
  class node_845 func_style
  node_846{"   ❓ ЕСЛИ (if)   " }
  node_838 -- " <font color='black'><b>далее</b></font> " ----> node_846
  class node_846 logic_style
  node_847["   ⚖️ РАВНО (==)    " ]
  node_846 -- " <font color='black'><b>далее</b></font> " ----> node_847
  class node_847 op_style
  node_848(["   🔍 intChoice   " ])
  node_847 -- " <font color='black'><b>далее</b></font> " ----> node_848
  node_849["   💎 5   "]
  node_847 -- " <font color='black'><b>далее</b></font> " ----> node_849
  node_850["   📂 БЛОК КОДА { }   " ]
  node_846 -- " <font color='black'><b>далее</b></font> " ----> node_850
  node_851{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_850 -- " <font color='black'><b>далее</b></font> " ----> node_851
  class node_851 var_style
  node_852(["   ИМЯ: taskIdInput
Тип: auto   " ])
  node_851 -- " <font color='black'><b>память</b></font> " ----> node_852
  node_853(["   🚀 ВЫЗОВ: input()   " ])
  node_852 -- " <font color='black'><b>далее</b></font> " ----> node_853
  class node_853 func_style
  node_854["   💎 Enter task ID to complete:    "]
  node_853 -- " <font color='black'><b>далее</b></font> " ----> node_854
  node_855{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_850 -- " <font color='black'><b>далее</b></font> " ----> node_855
  class node_855 var_style
  node_856(["   ИМЯ: taskId
Тип: auto   " ])
  node_855 -- " <font color='black'><b>память</b></font> " ----> node_856
  node_857(["   🚀 ВЫЗОВ: int()   " ])
  node_856 -- " <font color='black'><b>далее</b></font> " ----> node_857
  class node_857 func_style
  node_858(["   🔍 taskIdInput   " ])
  node_857 -- " <font color='black'><b>далее</b></font> " ----> node_858
  node_859["   ⚙️ ОПЕРАЦИЯ    " ]
  node_850 -- " <font color='black'><b>далее</b></font> " ----> node_859
  class node_859 op_style
  node_860(["   🔍 currentUser   " ])
  node_859 -- " <font color='black'><b>далее</b></font> " ----> node_860
  node_861(["   🚀 ВЫЗОВ: completeTask()   " ])
  node_859 -- " <font color='black'><b>далее</b></font> " ----> node_861
  class node_861 func_style
  node_862(["   🔍 taskId   " ])
  node_861 -- " <font color='black'><b>далее</b></font> " ----> node_862
  node_863{"   ❓ ЕСЛИ (if)   " }
  node_846 -- " <font color='black'><b>далее</b></font> " ----> node_863
  class node_863 logic_style
  node_864["   ⚖️ РАВНО (==)    " ]
  node_863 -- " <font color='black'><b>далее</b></font> " ----> node_864
  class node_864 op_style
  node_865(["   🔍 intChoice   " ])
  node_864 -- " <font color='black'><b>далее</b></font> " ----> node_865
  node_866["   💎 6   "]
  node_864 -- " <font color='black'><b>далее</b></font> " ----> node_866
  node_867["   📂 БЛОК КОДА { }   " ]
  node_863 -- " <font color='black'><b>далее</b></font> " ----> node_867
  node_868{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_867 -- " <font color='black'><b>далее</b></font> " ----> node_868
  class node_868 var_style
  node_869(["   ИМЯ: taskIdInput
Тип: auto   " ])
  node_868 -- " <font color='black'><b>память</b></font> " ----> node_869
  node_870(["   🚀 ВЫЗОВ: input()   " ])
  node_869 -- " <font color='black'><b>далее</b></font> " ----> node_870
  class node_870 func_style
  node_871["   💎 Enter task ID to reopen:    "]
  node_870 -- " <font color='black'><b>далее</b></font> " ----> node_871
  node_872{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_867 -- " <font color='black'><b>далее</b></font> " ----> node_872
  class node_872 var_style
  node_873(["   ИМЯ: taskId
Тип: auto   " ])
  node_872 -- " <font color='black'><b>память</b></font> " ----> node_873
  node_874(["   🚀 ВЫЗОВ: int()   " ])
  node_873 -- " <font color='black'><b>далее</b></font> " ----> node_874
  class node_874 func_style
  node_875(["   🔍 taskIdInput   " ])
  node_874 -- " <font color='black'><b>далее</b></font> " ----> node_875
  node_876["   ⚙️ ОПЕРАЦИЯ    " ]
  node_867 -- " <font color='black'><b>далее</b></font> " ----> node_876
  class node_876 op_style
  node_877(["   🔍 currentUser   " ])
  node_876 -- " <font color='black'><b>далее</b></font> " ----> node_877
  node_878(["   🚀 ВЫЗОВ: uncompleteTask()   " ])
  node_876 -- " <font color='black'><b>далее</b></font> " ----> node_878
  class node_878 func_style
  node_879(["   🔍 taskId   " ])
  node_878 -- " <font color='black'><b>далее</b></font> " ----> node_879
  node_880{"   ❓ ЕСЛИ (if)   " }
  node_863 -- " <font color='black'><b>далее</b></font> " ----> node_880
  class node_880 logic_style
  node_881["   ⚖️ РАВНО (==)    " ]
  node_880 -- " <font color='black'><b>далее</b></font> " ----> node_881
  class node_881 op_style
  node_882(["   🔍 intChoice   " ])
  node_881 -- " <font color='black'><b>далее</b></font> " ----> node_882
  node_883["   💎 7   "]
  node_881 -- " <font color='black'><b>далее</b></font> " ----> node_883
  node_884["   📂 БЛОК КОДА { }   " ]
  node_880 -- " <font color='black'><b>далее</b></font> " ----> node_884
  node_885{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_884 -- " <font color='black'><b>далее</b></font> " ----> node_885
  class node_885 var_style
  node_886(["   ИМЯ: taskIdInput
Тип: auto   " ])
  node_885 -- " <font color='black'><b>память</b></font> " ----> node_886
  node_887(["   🚀 ВЫЗОВ: input()   " ])
  node_886 -- " <font color='black'><b>далее</b></font> " ----> node_887
  class node_887 func_style
  node_888["   💎 Enter task ID to remove:    "]
  node_887 -- " <font color='black'><b>далее</b></font> " ----> node_888
  node_889{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_884 -- " <font color='black'><b>далее</b></font> " ----> node_889
  class node_889 var_style
  node_890(["   ИМЯ: taskId
Тип: auto   " ])
  node_889 -- " <font color='black'><b>память</b></font> " ----> node_890
  node_891(["   🚀 ВЫЗОВ: int()   " ])
  node_890 -- " <font color='black'><b>далее</b></font> " ----> node_891
  class node_891 func_style
  node_892(["   🔍 taskIdInput   " ])
  node_891 -- " <font color='black'><b>далее</b></font> " ----> node_892
  node_893["   ⚙️ ОПЕРАЦИЯ    " ]
  node_884 -- " <font color='black'><b>далее</b></font> " ----> node_893
  class node_893 op_style
  node_894(["   🔍 currentUser   " ])
  node_893 -- " <font color='black'><b>далее</b></font> " ----> node_894
  node_895(["   🚀 ВЫЗОВ: removeTask()   " ])
  node_893 -- " <font color='black'><b>далее</b></font> " ----> node_895
  class node_895 func_style
  node_896(["   🔍 taskId   " ])
  node_895 -- " <font color='black'><b>далее</b></font> " ----> node_896
  node_897{"   ❓ ЕСЛИ (if)   " }
  node_880 -- " <font color='black'><b>далее</b></font> " ----> node_897
  class node_897 logic_style
  node_898["   ⚖️ РАВНО (==)    " ]
  node_897 -- " <font color='black'><b>далее</b></font> " ----> node_898
  class node_898 op_style
  node_899(["   🔍 intChoice   " ])
  node_898 -- " <font color='black'><b>далее</b></font> " ----> node_899
  node_900["   💎 8   "]
  node_898 -- " <font color='black'><b>далее</b></font> " ----> node_900
  node_901["   📂 БЛОК КОДА { }   " ]
  node_897 -- " <font color='black'><b>далее</b></font> " ----> node_901
  node_902["   ⚙️ ОПЕРАЦИЯ    " ]
  node_901 -- " <font color='black'><b>далее</b></font> " ----> node_902
  class node_902 op_style
  node_903(["   🔍 currentUser   " ])
  node_902 -- " <font color='black'><b>далее</b></font> " ----> node_903
  node_904(["   🚀 ВЫЗОВ: getStats()   " ])
  node_902 -- " <font color='black'><b>далее</b></font> " ----> node_904
  class node_904 func_style
  node_905{"   ❓ ЕСЛИ (if)   " }
  node_897 -- " <font color='black'><b>далее</b></font> " ----> node_905
  class node_905 logic_style
  node_906["   ⚖️ РАВНО (==)    " ]
  node_905 -- " <font color='black'><b>далее</b></font> " ----> node_906
  class node_906 op_style
  node_907(["   🔍 intChoice   " ])
  node_906 -- " <font color='black'><b>далее</b></font> " ----> node_907
  node_908["   💎 9   "]
  node_906 -- " <font color='black'><b>далее</b></font> " ----> node_908
  node_909["   📂 БЛОК КОДА { }   " ]
  node_905 -- " <font color='black'><b>далее</b></font> " ----> node_909
  node_910{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_909 -- " <font color='black'><b>далее</b></font> " ----> node_910
  class node_910 var_style
  node_911(["   ИМЯ: priorityInput
Тип: auto   " ])
  node_910 -- " <font color='black'><b>память</b></font> " ----> node_911
  node_912(["   🚀 ВЫЗОВ: input()   " ])
  node_911 -- " <font color='black'><b>далее</b></font> " ----> node_912
  class node_912 func_style
  node_913["   💎 Enter priority (1=High, 2=Medium, 3=Low):    "]
  node_912 -- " <font color='black'><b>далее</b></font> " ----> node_913
  node_914{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_909 -- " <font color='black'><b>далее</b></font> " ----> node_914
  class node_914 var_style
  node_915(["   ИМЯ: priority
Тип: auto   " ])
  node_914 -- " <font color='black'><b>память</b></font> " ----> node_915
  node_916(["   🚀 ВЫЗОВ: int()   " ])
  node_915 -- " <font color='black'><b>далее</b></font> " ----> node_916
  class node_916 func_style
  node_917(["   🔍 priorityInput   " ])
  node_916 -- " <font color='black'><b>далее</b></font> " ----> node_917
  node_918{"   ❓ ЕСЛИ (if)   " }
  node_909 -- " <font color='black'><b>далее</b></font> " ----> node_918
  class node_918 logic_style
  node_919["   🧠 ЛОГИЧ. И (&)    " ]
  node_918 -- " <font color='black'><b>далее</b></font> " ----> node_919
  class node_919 op_style
  node_920["   📈 БОЛЬШЕ-РАВНО (>=)    " ]
  node_919 -- " <font color='black'><b>далее</b></font> " ----> node_920
  class node_920 op_style
  node_921(["   🔍 priority   " ])
  node_920 -- " <font color='black'><b>далее</b></font> " ----> node_921
  node_922["   💎 1   "]
  node_920 -- " <font color='black'><b>далее</b></font> " ----> node_922
  node_923["   📉 МЕНЬШЕ-РАВНО (<=)    " ]
  node_919 -- " <font color='black'><b>далее</b></font> " ----> node_923
  class node_923 op_style
  node_924(["   🔍 priority   " ])
  node_923 -- " <font color='black'><b>далее</b></font> " ----> node_924
  node_925["   💎 3   "]
  node_923 -- " <font color='black'><b>далее</b></font> " ----> node_925
  node_926["   📂 БЛОК КОДА { }   " ]
  node_918 -- " <font color='black'><b>далее</b></font> " ----> node_926
  node_927{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_926 -- " <font color='black'><b>далее</b></font> " ----> node_927
  class node_927 var_style
  node_928(["   ИМЯ: tasks
Тип: auto   " ])
  node_927 -- " <font color='black'><b>память</b></font> " ----> node_928
  node_929["   ⚙️ ОПЕРАЦИЯ    " ]
  node_928 -- " <font color='black'><b>далее</b></font> " ----> node_929
  class node_929 op_style
  node_930(["   🔍 currentUser   " ])
  node_929 -- " <font color='black'><b>далее</b></font> " ----> node_930
  node_931(["   🚀 ВЫЗОВ: findTasksByPriority()   " ])
  node_929 -- " <font color='black'><b>далее</b></font> " ----> node_931
  class node_931 func_style
  node_932(["   🔍 priority   " ])
  node_931 -- " <font color='black'><b>далее</b></font> " ----> node_932
  node_933(["   🚀 ВЫЗОВ: print()   " ])
  node_926 -- " <font color='black'><b>далее</b></font> " ----> node_933
  class node_933 func_style
  node_934["   💎     "]
  node_933 -- " <font color='black'><b>далее</b></font> " ----> node_934
  node_935(["   🚀 ВЫЗОВ: print()   " ])
  node_926 -- " <font color='black'><b>далее</b></font> " ----> node_935
  class node_935 func_style
  node_936["   ➕ СЛОЖИТЬ (+)    " ]
  node_935 -- " <font color='black'><b>далее</b></font> " ----> node_936
  class node_936 op_style
  node_937["   ➕ СЛОЖИТЬ (+)    " ]
  node_936 -- " <font color='black'><b>далее</b></font> " ----> node_937
  class node_937 op_style
  node_938["   💎 === Tasks with priority    "]
  node_937 -- " <font color='black'><b>далее</b></font> " ----> node_938
  node_939(["   🔍 priority   " ])
  node_937 -- " <font color='black'><b>далее</b></font> " ----> node_939
  node_940["   💎  ===   "]
  node_936 -- " <font color='black'><b>далее</b></font> " ----> node_940
  node_941{"   ❓ ЕСЛИ (if)   " }
  node_926 -- " <font color='black'><b>далее</b></font> " ----> node_941
  class node_941 logic_style
  node_942["   ⚖️ РАВНО (==)    " ]
  node_941 -- " <font color='black'><b>далее</b></font> " ----> node_942
  class node_942 op_style
  node_943(["   🚀 ВЫЗОВ: len()   " ])
  node_942 -- " <font color='black'><b>далее</b></font> " ----> node_943
  class node_943 func_style
  node_944(["   🔍 tasks   " ])
  node_943 -- " <font color='black'><b>далее</b></font> " ----> node_944
  node_945["   💎 0   "]
  node_942 -- " <font color='black'><b>далее</b></font> " ----> node_945
  node_946["   📂 БЛОК КОДА { }   " ]
  node_941 -- " <font color='black'><b>далее</b></font> " ----> node_946
  node_947(["   🚀 ВЫЗОВ: print()   " ])
  node_946 -- " <font color='black'><b>далее</b></font> " ----> node_947
  class node_947 func_style
  node_948["   💎 No tasks found   "]
  node_947 -- " <font color='black'><b>далее</b></font> " ----> node_948
  node_949["   📂 БЛОК КОДА { }   " ]
  node_941 -- " <font color='black'><b>далее</b></font> " ----> node_949
  node_950{{"   ♻️ ЦИКЛ: for (task)   " }}
  node_949 -- " <font color='black'><b>далее</b></font> " ----> node_950
  class node_950 logic_style
  node_951(["   🔍 tasks   " ])
  node_950 -- " <font color='black'><b>далее</b></font> " ----> node_951
  node_952["   📂 БЛОК КОДА { }   " ]
  node_950 -- " <font color='black'><b>далее</b></font> " ----> node_952
  node_953(["   🚀 ВЫЗОВ: print()   " ])
  node_952 -- " <font color='black'><b>далее</b></font> " ----> node_953
  class node_953 func_style
  node_954["   ⚙️ ОПЕРАЦИЯ    " ]
  node_953 -- " <font color='black'><b>далее</b></font> " ----> node_954
  class node_954 op_style
  node_955(["   🔍 task   " ])
  node_954 -- " <font color='black'><b>далее</b></font> " ----> node_955
  node_956(["   🚀 ВЫЗОВ: toString()   " ])
  node_954 -- " <font color='black'><b>далее</b></font> " ----> node_956
  class node_956 func_style
  node_957(["   🚀 ВЫЗОВ: print()   " ])
  node_926 -- " <font color='black'><b>далее</b></font> " ----> node_957
  class node_957 func_style
  node_958["   💎 ===================================   "]
  node_957 -- " <font color='black'><b>далее</b></font> " ----> node_958
  node_959(["   🚀 ВЫЗОВ: print()   " ])
  node_926 -- " <font color='black'><b>далее</b></font> " ----> node_959
  class node_959 func_style
  node_960["   💎     "]
  node_959 -- " <font color='black'><b>далее</b></font> " ----> node_960
  node_961["   📂 БЛОК КОДА { }   " ]
  node_918 -- " <font color='black'><b>далее</b></font> " ----> node_961
  node_962(["   🚀 ВЫЗОВ: print()   " ])
  node_961 -- " <font color='black'><b>далее</b></font> " ----> node_962
  class node_962 func_style
  node_963["   💎 Invalid priority   "]
  node_962 -- " <font color='black'><b>далее</b></font> " ----> node_963
  node_964{"   ❓ ЕСЛИ (if)   " }
  node_905 -- " <font color='black'><b>далее</b></font> " ----> node_964
  class node_964 logic_style
  node_965["   ⚖️ РАВНО (==)    " ]
  node_964 -- " <font color='black'><b>далее</b></font> " ----> node_965
  class node_965 op_style
  node_966(["   🔍 intChoice   " ])
  node_965 -- " <font color='black'><b>далее</b></font> " ----> node_966
  node_967["   💎 10   "]
  node_965 -- " <font color='black'><b>далее</b></font> " ----> node_967
  node_968["   📂 БЛОК КОДА { }   " ]
  node_964 -- " <font color='black'><b>далее</b></font> " ----> node_968
  node_969(["   🚀 ВЫЗОВ: print()   " ])
  node_968 -- " <font color='black'><b>далее</b></font> " ----> node_969
  class node_969 func_style
  node_970["   💎 Goodbye!   "]
  node_969 -- " <font color='black'><b>далее</b></font> " ----> node_970
  node_971["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_968 -- " <font color='black'><b>далее</b></font> " ----> node_971
  class node_971 op_style
  node_972(["   🔍 running   " ])
  node_971 -- " <font color='black'><b>далее</b></font> " ----> node_972
  node_973["   💎 false   "]
  node_971 -- " <font color='black'><b>далее</b></font> " ----> node_973
  node_974["   📂 БЛОК КОДА { }   " ]
  node_964 -- " <font color='black'><b>далее</b></font> " ----> node_974
  node_975(["   🚀 ВЫЗОВ: print()   " ])
  node_974 -- " <font color='black'><b>далее</b></font> " ----> node_975
  class node_975 func_style
  node_976["   💎 Invalid choice. Please try again.   "]
  node_975 -- " <font color='black'><b>далее</b></font> " ----> node_976
  node_977{{"   🧪 ТЕСТ: TesrSystem   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_977
  class node_977 test_style
  node_978["   📂 БЛОК КОДА { }   " ]
  node_977 -- " <font color='black'><b>далее</b></font> " ----> node_978
  node_979{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_978 -- " <font color='black'><b>далее</b></font> " ----> node_979
  class node_979 var_style
  node_980(["   ИМЯ: testUser
Тип: auto   " ])
  node_979 -- " <font color='black'><b>память</b></font> " ----> node_980
  node_981(["   🚀 ВЫЗОВ: User()   " ])
  node_980 -- " <font color='black'><b>далее</b></font> " ----> node_981
  class node_981 func_style
  node_982["   💎 99   "]
  node_981 -- " <font color='black'><b>далее</b></font> " ----> node_982
  node_983["   💎 Test User   "]
  node_981 -- " <font color='black'><b>далее</b></font> " ----> node_983
  node_984["   ⚙️ ОПЕРАЦИЯ    " ]
  node_978 -- " <font color='black'><b>далее</b></font> " ----> node_984
  class node_984 op_style
  node_985(["   🔍 testUser   " ])
  node_984 -- " <font color='black'><b>далее</b></font> " ----> node_985
  node_986(["   🚀 ВЫЗОВ: addTask()   " ])
  node_984 -- " <font color='black'><b>далее</b></font> " ----> node_986
  class node_986 func_style
  node_987["   💎 Complete project   "]
  node_986 -- " <font color='black'><b>далее</b></font> " ----> node_987
  node_988["   💎 Finish the ATM language project   "]
  node_986 -- " <font color='black'><b>далее</b></font> " ----> node_988
  node_989["   💎 1   "]
  node_986 -- " <font color='black'><b>далее</b></font> " ----> node_989
  node_990["   ⚙️ ОПЕРАЦИЯ    " ]
  node_978 -- " <font color='black'><b>далее</b></font> " ----> node_990
  class node_990 op_style
  node_991(["   🔍 testUser   " ])
  node_990 -- " <font color='black'><b>далее</b></font> " ----> node_991
  node_992(["   🚀 ВЫЗОВ: addTask()   " ])
  node_990 -- " <font color='black'><b>далее</b></font> " ----> node_992
  class node_992 func_style
  node_993["   💎 Buy groceries   "]
  node_992 -- " <font color='black'><b>далее</b></font> " ----> node_993
  node_994["   💎 Milk, eggs, bread   "]
  node_992 -- " <font color='black'><b>далее</b></font> " ----> node_994
  node_995["   💎 3   "]
  node_992 -- " <font color='black'><b>далее</b></font> " ----> node_995
  node_996["   ⚙️ ОПЕРАЦИЯ    " ]
  node_978 -- " <font color='black'><b>далее</b></font> " ----> node_996
  class node_996 op_style
  node_997(["   🔍 testUser   " ])
  node_996 -- " <font color='black'><b>далее</b></font> " ----> node_997
  node_998(["   🚀 ВЫЗОВ: addTask()   " ])
  node_996 -- " <font color='black'><b>далее</b></font> " ----> node_998
  class node_998 func_style
  node_999["   💎 Read book   "]
  node_998 -- " <font color='black'><b>далее</b></font> " ----> node_999
  node_1000["   💎 Read 50 pages   "]
  node_998 -- " <font color='black'><b>далее</b></font> " ----> node_1000
  node_1001["   💎 2   "]
  node_998 -- " <font color='black'><b>далее</b></font> " ----> node_1001
  node_1002[/"   ✅ ASSERT   " /]
  node_978 -- " <font color='black'><b>далее</b></font> " ----> node_1002
  class node_1002 assert_style
  node_1003["   ⚖️ РАВНО (==)    " ]
  node_1002 -- " <font color='black'><b>далее</b></font> " ----> node_1003
  class node_1003 op_style
  node_1004(["   🚀 ВЫЗОВ: len()   " ])
  node_1003 -- " <font color='black'><b>далее</b></font> " ----> node_1004
  class node_1004 func_style
  node_1005["   ⚙️ ОПЕРАЦИЯ    " ]
  node_1004 -- " <font color='black'><b>далее</b></font> " ----> node_1005
  class node_1005 op_style
  node_1006(["   🔍 testUser   " ])
  node_1005 -- " <font color='black'><b>далее</b></font> " ----> node_1006
  node_1007(["   🚀 ВЫЗОВ: tasks()   " ])
  node_1005 -- " <font color='black'><b>далее</b></font> " ----> node_1007
  class node_1007 func_style
  node_1008["   💎 3   "]
  node_1003 -- " <font color='black'><b>далее</b></font> " ----> node_1008
  node_1009["   ⚙️ ОПЕРАЦИЯ    " ]
  node_978 -- " <font color='black'><b>далее</b></font> " ----> node_1009
  class node_1009 op_style
  node_1010(["   🔍 testUser   " ])
  node_1009 -- " <font color='black'><b>далее</b></font> " ----> node_1010
  node_1011(["   🚀 ВЫЗОВ: completeTask()   " ])
  node_1009 -- " <font color='black'><b>далее</b></font> " ----> node_1011
  class node_1011 func_style
  node_1012["   💎 1   "]
  node_1011 -- " <font color='black'><b>далее</b></font> " ----> node_1012
  node_1013{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_978 -- " <font color='black'><b>далее</b></font> " ----> node_1013
  class node_1013 var_style
  node_1014(["   ИМЯ: task
Тип: auto   " ])
  node_1013 -- " <font color='black'><b>память</b></font> " ----> node_1014
  node_1015["   ⚙️ ОПЕРАЦИЯ    " ]
  node_1014 -- " <font color='black'><b>далее</b></font> " ----> node_1015
  class node_1015 op_style
  node_1016(["   🔍 testUser   " ])
  node_1015 -- " <font color='black'><b>далее</b></font> " ----> node_1016
  node_1017(["   🚀 ВЫЗОВ: findTaskById()   " ])
  node_1015 -- " <font color='black'><b>далее</b></font> " ----> node_1017
  class node_1017 func_style
  node_1018["   💎 1   "]
  node_1017 -- " <font color='black'><b>далее</b></font> " ----> node_1018
  node_1019[/"   ✅ ASSERT   " /]
  node_978 -- " <font color='black'><b>далее</b></font> " ----> node_1019
  class node_1019 assert_style
  node_1020["   ⚖️ РАВНО (==)    " ]
  node_1019 -- " <font color='black'><b>далее</b></font> " ----> node_1020
  class node_1020 op_style
  node_1021["   ⚙️ ОПЕРАЦИЯ    " ]
  node_1020 -- " <font color='black'><b>далее</b></font> " ----> node_1021
  class node_1021 op_style
  node_1022(["   🔍 task   " ])
  node_1021 -- " <font color='black'><b>далее</b></font> " ----> node_1022
  node_1023(["   🚀 ВЫЗОВ: completed()   " ])
  node_1021 -- " <font color='black'><b>далее</b></font> " ----> node_1023
  class node_1023 func_style
  node_1024["   💎 true   "]
  node_1020 -- " <font color='black'><b>далее</b></font> " ----> node_1024
  node_1025["   ⚙️ ОПЕРАЦИЯ    " ]
  node_978 -- " <font color='black'><b>далее</b></font> " ----> node_1025
  class node_1025 op_style
  node_1026(["   🔍 testUser   " ])
  node_1025 -- " <font color='black'><b>далее</b></font> " ----> node_1026
  node_1027(["   🚀 ВЫЗОВ: uncompleteTask()   " ])
  node_1025 -- " <font color='black'><b>далее</b></font> " ----> node_1027
  class node_1027 func_style
  node_1028["   💎 1   "]
  node_1027 -- " <font color='black'><b>далее</b></font> " ----> node_1028
  node_1029[/"   ✅ ASSERT   " /]
  node_978 -- " <font color='black'><b>далее</b></font> " ----> node_1029
  class node_1029 assert_style
  node_1030["   ⚖️ РАВНО (==)    " ]
  node_1029 -- " <font color='black'><b>далее</b></font> " ----> node_1030
  class node_1030 op_style
  node_1031["   ⚙️ ОПЕРАЦИЯ    " ]
  node_1030 -- " <font color='black'><b>далее</b></font> " ----> node_1031
  class node_1031 op_style
  node_1032(["   🔍 task   " ])
  node_1031 -- " <font color='black'><b>далее</b></font> " ----> node_1032
  node_1033(["   🚀 ВЫЗОВ: completed()   " ])
  node_1031 -- " <font color='black'><b>далее</b></font> " ----> node_1033
  class node_1033 func_style
  node_1034["   💎 false   "]
  node_1030 -- " <font color='black'><b>далее</b></font> " ----> node_1034
  node_1035["   ⚙️ ОПЕРАЦИЯ    " ]
  node_978 -- " <font color='black'><b>далее</b></font> " ----> node_1035
  class node_1035 op_style
  node_1036(["   🔍 testUser   " ])
  node_1035 -- " <font color='black'><b>далее</b></font> " ----> node_1036
  node_1037(["   🚀 ВЫЗОВ: removeTask()   " ])
  node_1035 -- " <font color='black'><b>далее</b></font> " ----> node_1037
  class node_1037 func_style
  node_1038["   💎 2   "]
  node_1037 -- " <font color='black'><b>далее</b></font> " ----> node_1038
  node_1039[/"   ✅ ASSERT   " /]
  node_978 -- " <font color='black'><b>далее</b></font> " ----> node_1039
  class node_1039 assert_style
  node_1040["   ⚖️ РАВНО (==)    " ]
  node_1039 -- " <font color='black'><b>далее</b></font> " ----> node_1040
  class node_1040 op_style
  node_1041(["   🚀 ВЫЗОВ: len()   " ])
  node_1040 -- " <font color='black'><b>далее</b></font> " ----> node_1041
  class node_1041 func_style
  node_1042["   ⚙️ ОПЕРАЦИЯ    " ]
  node_1041 -- " <font color='black'><b>далее</b></font> " ----> node_1042
  class node_1042 op_style
  node_1043(["   🔍 testUser   " ])
  node_1042 -- " <font color='black'><b>далее</b></font> " ----> node_1043
  node_1044(["   🚀 ВЫЗОВ: tasks()   " ])
  node_1042 -- " <font color='black'><b>далее</b></font> " ----> node_1044
  class node_1044 func_style
  node_1045["   💎 2   "]
  node_1040 -- " <font color='black'><b>далее</b></font> " ----> node_1045
  node_1046{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_978 -- " <font color='black'><b>далее</b></font> " ----> node_1046
  class node_1046 var_style
  node_1047(["   ИМЯ: highPriorityTasks
Тип: auto   " ])
  node_1046 -- " <font color='black'><b>память</b></font> " ----> node_1047
  node_1048["   ⚙️ ОПЕРАЦИЯ    " ]
  node_1047 -- " <font color='black'><b>далее</b></font> " ----> node_1048
  class node_1048 op_style
  node_1049(["   🔍 testUser   " ])
  node_1048 -- " <font color='black'><b>далее</b></font> " ----> node_1049
  node_1050(["   🚀 ВЫЗОВ: findTasksByPriority()   " ])
  node_1048 -- " <font color='black'><b>далее</b></font> " ----> node_1050
  class node_1050 func_style
  node_1051["   💎 1   "]
  node_1050 -- " <font color='black'><b>далее</b></font> " ----> node_1051
  node_1052[/"   ✅ ASSERT   " /]
  node_978 -- " <font color='black'><b>далее</b></font> " ----> node_1052
  class node_1052 assert_style
  node_1053["   ⚖️ РАВНО (==)    " ]
  node_1052 -- " <font color='black'><b>далее</b></font> " ----> node_1053
  class node_1053 op_style
  node_1054(["   🚀 ВЫЗОВ: len()   " ])
  node_1053 -- " <font color='black'><b>далее</b></font> " ----> node_1054
  class node_1054 func_style
  node_1055(["   🔍 highPriorityTasks   " ])
  node_1054 -- " <font color='black'><b>далее</b></font> " ----> node_1055
  node_1056["   💎 1   "]
  node_1053 -- " <font color='black'><b>далее</b></font> " ----> node_1056
  node_1057(["   🚀 ВЫЗОВ: print()   " ])
  node_978 -- " <font color='black'><b>далее</b></font> " ----> node_1057
  class node_1057 func_style
  node_1058["   💎 All tests passed!   "]
  node_1057 -- " <font color='black'><b>далее</b></font> " ----> node_1058
  node_1059(["   🚀 ВЫЗОВ: main()   " ])
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_1059
  class node_1059 func_style
```
