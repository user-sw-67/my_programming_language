```mermaid
%%{init: { 'theme': 'base', 'themeVariables': { 'primaryColor': '#ffffff', 'primaryTextColor': '#000000', 'lineColor': '#333333' }, 'graph': {'rankSep': 120, 'nodeSep': 100}} }%%
graph TD
  classDef root_style fill:#222,color:#fff,stroke:#000,stroke-width:4px;
  classDef var_style fill:#bbdefb,color:#000,stroke:#1565c0,stroke-width:2px;
  classDef op_style fill:#f3e5f5,color:#000,stroke:#7b1fa2,stroke-width:2px;
  classDef logic_style fill:#fff9c4,color:#000,stroke:#fbc02d,stroke-width:2px;
  classDef func_style fill:#c8e6c9,color:#000,stroke:#2e7d32,stroke-width:2px;
  node_0(("   🚀 КОРЕНЬ ПРОГРАММЫ   " ))
  class node_0 root_style
  node_1(["   🔍 Int   " ])
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_1
  node_2{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_2
  class node_2 var_style
  node_3(["   ИМЯ: x
Тип: auto   " ])
  node_2 -- " <font color='black'><b>память</b></font> " ----> node_3
  node_4["   💎 10   "]
  node_3 -- " <font color='black'><b>далее</b></font> " ----> node_4
  node_5(["   🔍 Double   " ])
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_5
  node_6{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_6
  class node_6 var_style
  node_7(["   ИМЯ: y
Тип: auto   " ])
  node_6 -- " <font color='black'><b>память</b></font> " ----> node_7
  node_8["   💎 10.9   "]
  node_7 -- " <font color='black'><b>далее</b></font> " ----> node_8
  node_9(["   🔍 Str   " ])
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_9
  node_10{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_10
  class node_10 var_style
  node_11(["   ИМЯ: name
Тип: auto   " ])
  node_10 -- " <font color='black'><b>память</b></font> " ----> node_11
  node_12["   💎 string   "]
  node_11 -- " <font color='black'><b>далее</b></font> " ----> node_12
  node_13(["   🔍 Bool   " ])
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_13
  node_14{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_14
  class node_14 var_style
  node_15(["   ИМЯ: flag
Тип: auto   " ])
  node_14 -- " <font color='black'><b>память</b></font> " ----> node_15
  node_16["   💎 true   "]
  node_15 -- " <font color='black'><b>далее</b></font> " ----> node_16
  node_17(["   🔍 Null   " ])
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_17
  node_18{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_18
  class node_18 var_style
  node_19(["   ИМЯ: empty
Тип: auto   " ])
  node_18 -- " <font color='black'><b>память</b></font> " ----> node_19
  node_20{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_20
  class node_20 var_style
  node_21(["   ИМЯ: nothing
Тип: auto   " ])
  node_20 -- " <font color='black'><b>память</b></font> " ----> node_21
  node_22["   💎 null   "]
  node_21 -- " <font color='black'><b>далее</b></font> " ----> node_22
  node_23{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_23
  class node_23 var_style
  node_24(["   ИМЯ: name_var0
Тип: auto   " ])
  node_23 -- " <font color='black'><b>память</b></font> " ----> node_24
  node_25{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_25
  class node_25 var_style
  node_26(["   ИМЯ: name_var1
Тип: auto   " ])
  node_25 -- " <font color='black'><b>память</b></font> " ----> node_26
  node_27["   💎 999   "]
  node_26 -- " <font color='black'><b>далее</b></font> " ----> node_27
  node_28{{"   🔒 КОНСТАНТЫ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_28
  class node_28 var_style
  node_29(["   ИМЯ: a
Тип: auto   " ])
  node_28 -- " <font color='black'><b>память</b></font> " ----> node_29
  node_30{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_30
  class node_30 var_style
  node_31(["   ИМЯ: a
Тип: auto   " ])
  node_30 -- " <font color='black'><b>память</b></font> " ----> node_31
  node_32["   💎 1   "]
  node_31 -- " <font color='black'><b>далее</b></font> " ----> node_32
  node_33(["   ИМЯ: b
Тип: auto   " ])
  node_30 -- " <font color='black'><b>память</b></font> " ----> node_33
  node_34["   💎 2   "]
  node_33 -- " <font color='black'><b>далее</b></font> " ----> node_34
  node_35(["   ИМЯ: c
Тип: auto   " ])
  node_30 -- " <font color='black'><b>память</b></font> " ----> node_35
  node_36["   💎 3   "]
  node_35 -- " <font color='black'><b>далее</b></font> " ----> node_36
  node_37{{"   🔒 КОНСТАНТЫ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_37
  class node_37 var_style
  node_38(["   ИМЯ: a
Тип: auto   " ])
  node_37 -- " <font color='black'><b>память</b></font> " ----> node_38
  node_39["   💎 1   "]
  node_38 -- " <font color='black'><b>далее</b></font> " ----> node_39
  node_40(["   ИМЯ: b
Тип: auto   " ])
  node_37 -- " <font color='black'><b>память</b></font> " ----> node_40
  node_41["   💎 2   "]
  node_40 -- " <font color='black'><b>далее</b></font> " ----> node_41
  node_42(["   ИМЯ: c
Тип: auto   " ])
  node_37 -- " <font color='black'><b>память</b></font> " ----> node_42
  node_43["   💎 3   "]
  node_42 -- " <font color='black'><b>далее</b></font> " ----> node_43
  node_44{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_44
  class node_44 var_style
  node_45(["   ИМЯ: x
Тип: auto   " ])
  node_44 -- " <font color='black'><b>память</b></font> " ----> node_45
  node_46["   💎 5   "]
  node_45 -- " <font color='black'><b>далее</b></font> " ----> node_46
  node_47["   ⚙️ ОПЕРАЦИЯ    " ]
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_47
  class node_47 op_style
  node_48(["   🔍 x   " ])
  node_47 -- " <font color='black'><b>далее</b></font> " ----> node_48
  node_49["   💎 3   "]
  node_47 -- " <font color='black'><b>далее</b></font> " ----> node_49
  node_50["   ⚙️ ОПЕРАЦИЯ    " ]
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_50
  class node_50 op_style
  node_51(["   🔍 x   " ])
  node_50 -- " <font color='black'><b>далее</b></font> " ----> node_51
  node_52["   💎 2   "]
  node_50 -- " <font color='black'><b>далее</b></font> " ----> node_52
  node_53["   ⚙️ ОПЕРАЦИЯ    " ]
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_53
  class node_53 op_style
  node_54(["   🔍 x   " ])
  node_53 -- " <font color='black'><b>далее</b></font> " ----> node_54
  node_55["   💎 4   "]
  node_53 -- " <font color='black'><b>далее</b></font> " ----> node_55
  node_56["   ⚙️ ОПЕРАЦИЯ    " ]
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_56
  class node_56 op_style
  node_57(["   🔍 x   " ])
  node_56 -- " <font color='black'><b>далее</b></font> " ----> node_57
  node_58["   💎 2   "]
  node_56 -- " <font color='black'><b>далее</b></font> " ----> node_58
  node_59["   ⚙️ ОПЕРАЦИЯ    " ]
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_59
  class node_59 op_style
  node_60(["   🔍 x   " ])
  node_59 -- " <font color='black'><b>далее</b></font> " ----> node_60
  node_61["   💎 2   "]
  node_59 -- " <font color='black'><b>далее</b></font> " ----> node_61
  node_62["   ⚙️ ОПЕРАЦИЯ    " ]
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_62
  class node_62 op_style
  node_63(["   🔍 x   " ])
  node_62 -- " <font color='black'><b>далее</b></font> " ----> node_63
  node_64["   💎 3   "]
  node_62 -- " <font color='black'><b>далее</b></font> " ----> node_64
  node_65["   ⚙️ ОПЕРАЦИЯ    " ]
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_65
  class node_65 op_style
  node_66(["   🔍 x   " ])
  node_65 -- " <font color='black'><b>далее</b></font> " ----> node_66
  node_67["   💎 2   "]
  node_65 -- " <font color='black'><b>далее</b></font> " ----> node_67
  node_68{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_68
  class node_68 var_style
  node_69(["   ИМЯ: x1
Тип: auto   " ])
  node_68 -- " <font color='black'><b>память</b></font> " ----> node_69
  node_70["   💎 8.9   "]
  node_69 -- " <font color='black'><b>далее</b></font> " ----> node_70
  node_71["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_71
  class node_71 op_style
  node_72(["   🔍 x1   " ])
  node_71 -- " <font color='black'><b>далее</b></font> " ----> node_72
  node_73["   💎 10   "]
  node_71 -- " <font color='black'><b>далее</b></font> " ----> node_73
  node_74["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_74
  class node_74 op_style
  node_75(["   🔍 x1   " ])
  node_74 -- " <font color='black'><b>далее</b></font> " ----> node_75
  node_76["   💎 hello   "]
  node_74 -- " <font color='black'><b>далее</b></font> " ----> node_76
  node_77["   📂 БЛОК КОДА { }   " ]
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_77
  node_78{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_77 -- " <font color='black'><b>далее</b></font> " ----> node_78
  class node_78 var_style
  node_79(["   ИМЯ: a
Тип: auto   " ])
  node_78 -- " <font color='black'><b>память</b></font> " ----> node_79
  node_80["   💎 0   "]
  node_79 -- " <font color='black'><b>далее</b></font> " ----> node_80
  node_81{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_81
  class node_81 var_style
  node_82(["   ИМЯ: a
Тип: auto   " ])
  node_81 -- " <font color='black'><b>память</b></font> " ----> node_82
  node_83["   💎 0   "]
  node_82 -- " <font color='black'><b>далее</b></font> " ----> node_83
  node_84["   📂 БЛОК КОДА { }   " ]
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_84
  node_85(["   🚀 ВЫЗОВ: print()   " ])
  node_84 -- " <font color='black'><b>далее</b></font> " ----> node_85
  class node_85 func_style
  node_86(["   🔍 a   " ])
  node_85 -- " <font color='black'><b>далее</b></font> " ----> node_86
  node_87["   📂 БЛОК КОДА { }   " ]
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_87
  node_88{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_87 -- " <font color='black'><b>далее</b></font> " ----> node_88
  class node_88 var_style
  node_89(["   ИМЯ: a
Тип: auto   " ])
  node_88 -- " <font color='black'><b>память</b></font> " ----> node_89
  node_90["   💎 1   "]
  node_89 -- " <font color='black'><b>далее</b></font> " ----> node_90
  node_91["   📂 БЛОК КОДА { }   " ]
  node_87 -- " <font color='black'><b>далее</b></font> " ----> node_91
  node_92{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_91 -- " <font color='black'><b>далее</b></font> " ----> node_92
  class node_92 var_style
  node_93(["   ИМЯ: a
Тип: auto   " ])
  node_92 -- " <font color='black'><b>память</b></font> " ----> node_93
  node_94["   💎 0   "]
  node_93 -- " <font color='black'><b>далее</b></font> " ----> node_94
  node_95(["   🚀 ВЫЗОВ: print()   " ])
  node_91 -- " <font color='black'><b>далее</b></font> " ----> node_95
  class node_95 func_style
  node_96(["   🔍 a   " ])
  node_95 -- " <font color='black'><b>далее</b></font> " ----> node_96
  node_97(["   🚀 ВЫЗОВ: print()   " ])
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_97
  class node_97 func_style
  node_98["   💎 eee   "]
  node_97 -- " <font color='black'><b>далее</b></font> " ----> node_98
  node_99(["   🚀 ВЫЗОВ: println()   " ])
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_99
  class node_99 func_style
  node_100["   💎 eee   "]
  node_99 -- " <font color='black'><b>далее</b></font> " ----> node_100
  node_101(["   🚀 ВЫЗОВ: printerr()   " ])
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_101
  class node_101 func_style
  node_102["   💎 eee   "]
  node_101 -- " <font color='black'><b>далее</b></font> " ----> node_102
  node_103(["   🚀 ВЫЗОВ: printerrln()   " ])
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_103
  class node_103 func_style
  node_104["   💎 eee   "]
  node_103 -- " <font color='black'><b>далее</b></font> " ----> node_104
  node_105(["   🚀 ВЫЗОВ: input()   " ])
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_105
  class node_105 func_style
  node_106["   💎 eee   "]
  node_105 -- " <font color='black'><b>далее</b></font> " ----> node_106
  node_107{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_107
  class node_107 var_style
  node_108(["   ИМЯ: x
Тип: auto   " ])
  node_107 -- " <font color='black'><b>память</b></font> " ----> node_108
  node_109["   💎 9   "]
  node_108 -- " <font color='black'><b>далее</b></font> " ----> node_109
  node_110{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_110
  class node_110 var_style
  node_111(["   ИМЯ: c
Тип: auto   " ])
  node_110 -- " <font color='black'><b>память</b></font> " ----> node_111
  node_112(["   🚀 ВЫЗОВ: str()   " ])
  node_111 -- " <font color='black'><b>далее</b></font> " ----> node_112
  class node_112 func_style
  node_113(["   🔍 x   " ])
  node_112 -- " <font color='black'><b>далее</b></font> " ----> node_113
  node_114{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_114
  class node_114 var_style
  node_115(["   ИМЯ: cq
Тип: auto   " ])
  node_114 -- " <font color='black'><b>память</b></font> " ----> node_115
  node_116(["   🚀 ВЫЗОВ: double()   " ])
  node_115 -- " <font color='black'><b>далее</b></font> " ----> node_116
  class node_116 func_style
  node_117(["   🔍 x   " ])
  node_116 -- " <font color='black'><b>далее</b></font> " ----> node_117
  node_118(["   🚀 ВЫЗОВ: print()   " ])
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_118
  class node_118 func_style
  node_119(["   🚀 ВЫЗОВ: type()   " ])
  node_118 -- " <font color='black'><b>далее</b></font> " ----> node_119
  class node_119 func_style
  node_120(["   🔍 c   " ])
  node_119 -- " <font color='black'><b>далее</b></font> " ----> node_120
  node_121(["   🚀 ВЫЗОВ: print()   " ])
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_121
  class node_121 func_style
  node_122(["   🚀 ВЫЗОВ: int()   " ])
  node_121 -- " <font color='black'><b>далее</b></font> " ----> node_122
  class node_122 func_style
  node_123(["   🔍 c   " ])
  node_122 -- " <font color='black'><b>далее</b></font> " ----> node_123
  node_124{"   ❓ ЕСЛИ (if)   " }
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_124
  class node_124 logic_style
  node_125["   📈 БОЛЬШЕ (>)    " ]
  node_124 -- " <font color='black'><b>далее</b></font> " ----> node_125
  class node_125 op_style
  node_126(["   🔍 x   " ])
  node_125 -- " <font color='black'><b>далее</b></font> " ----> node_126
  node_127["   💎 10   "]
  node_125 -- " <font color='black'><b>далее</b></font> " ----> node_127
  node_128["   📂 БЛОК КОДА { }   " ]
  node_124 -- " <font color='black'><b>далее</b></font> " ----> node_128
  node_129(["   🚀 ВЫЗОВ: print()   " ])
  node_128 -- " <font color='black'><b>далее</b></font> " ----> node_129
  class node_129 func_style
  node_130["   💎 больше   "]
  node_129 -- " <font color='black'><b>далее</b></font> " ----> node_130
  node_131{"   ❓ ЕСЛИ (if)   " }
  node_124 -- " <font color='black'><b>далее</b></font> " ----> node_131
  class node_131 logic_style
  node_132["   📈 БОЛЬШЕ (>)    " ]
  node_131 -- " <font color='black'><b>далее</b></font> " ----> node_132
  class node_132 op_style
  node_133(["   🔍 x   " ])
  node_132 -- " <font color='black'><b>далее</b></font> " ----> node_133
  node_134["   💎 5   "]
  node_132 -- " <font color='black'><b>далее</b></font> " ----> node_134
  node_135["   📂 БЛОК КОДА { }   " ]
  node_131 -- " <font color='black'><b>далее</b></font> " ----> node_135
  node_136(["   🚀 ВЫЗОВ: print()   " ])
  node_135 -- " <font color='black'><b>далее</b></font> " ----> node_136
  class node_136 func_style
  node_137["   💎 средний   "]
  node_136 -- " <font color='black'><b>далее</b></font> " ----> node_137
  node_138["   📂 БЛОК КОДА { }   " ]
  node_131 -- " <font color='black'><b>далее</b></font> " ----> node_138
  node_139(["   🚀 ВЫЗОВ: print()   " ])
  node_138 -- " <font color='black'><b>далее</b></font> " ----> node_139
  class node_139 func_style
  node_140["   💎 маленький   "]
  node_139 -- " <font color='black'><b>далее</b></font> " ----> node_140
  node_141{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_141
  class node_141 var_style
  node_142(["   ИМЯ: status
Тип: auto   " ])
  node_141 -- " <font color='black'><b>память</b></font> " ----> node_142
  node_143{"   ⚖️ ТЕРНАРКА (?:)   " }
  node_142 -- " <font color='black'><b>далее</b></font> " ----> node_143
  class node_143 logic_style
  node_144["   📈 БОЛЬШЕ-РАВНО (>=)    " ]
  node_143 -- " <font color='black'><b>далее</b></font> " ----> node_144
  class node_144 op_style
  node_145(["   🔍 age   " ])
  node_144 -- " <font color='black'><b>далее</b></font> " ----> node_145
  node_146["   💎 18   "]
  node_144 -- " <font color='black'><b>далее</b></font> " ----> node_146
  node_147["   💎 взрослый   "]
  node_143 -- " <font color='black'><b>далее</b></font> " ----> node_147
  node_148["   💎 ребёнок   "]
  node_143 -- " <font color='black'><b>далее</b></font> " ----> node_148
  node_149{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_149
  class node_149 var_style
  node_150(["   ИМЯ: result
Тип: auto   " ])
  node_149 -- " <font color='black'><b>память</b></font> " ----> node_150
  node_151["   ➖ ВЫЧЕСТЬ (-)    " ]
  node_150 -- " <font color='black'><b>далее</b></font> " ----> node_151
  class node_151 op_style
  node_152["   ➕ СЛОЖИТЬ (+)    " ]
  node_151 -- " <font color='black'><b>далее</b></font> " ----> node_152
  class node_152 op_style
  node_153["   ➗ РАЗДЕЛИТЬ (/)    " ]
  node_152 -- " <font color='black'><b>далее</b></font> " ----> node_153
  class node_153 op_style
  node_154["   ✖️ УМНОЖИТЬ (*)    " ]
  node_153 -- " <font color='black'><b>далее</b></font> " ----> node_154
  class node_154 op_style
  node_155["   💎 3   "]
  node_154 -- " <font color='black'><b>далее</b></font> " ----> node_155
  node_156["   💎 4   "]
  node_154 -- " <font color='black'><b>далее</b></font> " ----> node_156
  node_157["   💎 2   "]
  node_153 -- " <font color='black'><b>далее</b></font> " ----> node_157
  node_158["   💎 4   "]
  node_152 -- " <font color='black'><b>далее</b></font> " ----> node_158
  node_159["   🔢 ОСТАТОК (%)    " ]
  node_151 -- " <font color='black'><b>далее</b></font> " ----> node_159
  class node_159 op_style
  node_160["   ⚡ СТЕПЕНЬ (^)    " ]
  node_159 -- " <font color='black'><b>далее</b></font> " ----> node_160
  class node_160 op_style
  node_161["   💎 8   "]
  node_160 -- " <font color='black'><b>далее</b></font> " ----> node_161
  node_162["   💎 6   "]
  node_160 -- " <font color='black'><b>далее</b></font> " ----> node_162
  node_163["   💎 5   "]
  node_159 -- " <font color='black'><b>далее</b></font> " ----> node_163
  node_164{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_164
  class node_164 var_style
  node_165(["   ИМЯ: cmp
Тип: auto   " ])
  node_164 -- " <font color='black'><b>память</b></font> " ----> node_165
  node_166["   🚫 НЕ РАВНО (!=)    " ]
  node_165 -- " <font color='black'><b>далее</b></font> " ----> node_166
  class node_166 op_style
  node_167["   ⚖️ РАВНО (==)    " ]
  node_166 -- " <font color='black'><b>далее</b></font> " ----> node_167
  class node_167 op_style
  node_168["   💎 3   "]
  node_167 -- " <font color='black'><b>далее</b></font> " ----> node_168
  node_169["   💎 4   "]
  node_167 -- " <font color='black'><b>далее</b></font> " ----> node_169
  node_170["   📈 БОЛЬШЕ-РАВНО (>=)    " ]
  node_166 -- " <font color='black'><b>далее</b></font> " ----> node_170
  class node_170 op_style
  node_171["   📉 МЕНЬШЕ-РАВНО (<=)    " ]
  node_170 -- " <font color='black'><b>далее</b></font> " ----> node_171
  class node_171 op_style
  node_172["   📉 МЕНЬШЕ (<)    " ]
  node_171 -- " <font color='black'><b>далее</b></font> " ----> node_172
  class node_172 op_style
  node_173["   📈 БОЛЬШЕ (>)    " ]
  node_172 -- " <font color='black'><b>далее</b></font> " ----> node_173
  class node_173 op_style
  node_174["   💎 2   "]
  node_173 -- " <font color='black'><b>далее</b></font> " ----> node_174
  node_175["   💎 4   "]
  node_173 -- " <font color='black'><b>далее</b></font> " ----> node_175
  node_176["   💎 5   "]
  node_172 -- " <font color='black'><b>далее</b></font> " ----> node_176
  node_177["   💎 9   "]
  node_171 -- " <font color='black'><b>далее</b></font> " ----> node_177
  node_178["   💎 0   "]
  node_170 -- " <font color='black'><b>далее</b></font> " ----> node_178
  node_179{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_179
  class node_179 var_style
  node_180(["   ИМЯ: logic
Тип: auto   " ])
  node_179 -- " <font color='black'><b>память</b></font> " ----> node_180
  node_181["   🧠 ЛОГИЧ. ИЛИ (|)    " ]
  node_180 -- " <font color='black'><b>далее</b></font> " ----> node_181
  class node_181 op_style
  node_182["   🧠 ЛОГИЧ. И (&)    " ]
  node_181 -- " <font color='black'><b>далее</b></font> " ----> node_182
  class node_182 op_style
  node_183(["   🔍 a   " ])
  node_182 -- " <font color='black'><b>далее</b></font> " ----> node_183
  node_184(["   🔍 b   " ])
  node_182 -- " <font color='black'><b>далее</b></font> " ----> node_184
  node_185(["   ❗ ОТРИЦАНИЕ (!)    " ])
  node_181 -- " <font color='black'><b>далее</b></font> " ----> node_185
  class node_185 op_style
  node_186(["   🔍 c   " ])
  node_185 -- " <font color='black'><b>далее</b></font> " ----> node_186
  node_187{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_187
  class node_187 var_style
  node_188(["   ИМЯ: i
Тип: auto   " ])
  node_187 -- " <font color='black'><b>память</b></font> " ----> node_188
  node_189["   💎 0   "]
  node_188 -- " <font color='black'><b>далее</b></font> " ----> node_189
  node_190{{"   🔄 ЦИКЛ: while   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_190
  class node_190 logic_style
  node_191["   📉 МЕНЬШЕ (<)    " ]
  node_190 -- " <font color='black'><b>далее</b></font> " ----> node_191
  class node_191 op_style
  node_192(["   🔍 i   " ])
  node_191 -- " <font color='black'><b>далее</b></font> " ----> node_192
  node_193["   💎 10   "]
  node_191 -- " <font color='black'><b>далее</b></font> " ----> node_193
  node_194["   📂 БЛОК КОДА { }   " ]
  node_190 -- " <font color='black'><b>далее</b></font> " ----> node_194
  node_195(["   🚀 ВЫЗОВ: print()   " ])
  node_194 -- " <font color='black'><b>далее</b></font> " ----> node_195
  class node_195 func_style
  node_196(["   🔍 i   " ])
  node_195 -- " <font color='black'><b>далее</b></font> " ----> node_196
  node_197["   ⬅️ ПРИСВОИТЬ (=)    " ]
  node_194 -- " <font color='black'><b>далее</b></font> " ----> node_197
  class node_197 op_style
  node_198(["   🔍 i   " ])
  node_197 -- " <font color='black'><b>далее</b></font> " ----> node_198
  node_199["   ➕ СЛОЖИТЬ (+)    " ]
  node_197 -- " <font color='black'><b>далее</b></font> " ----> node_199
  class node_199 op_style
  node_200(["   🔍 i   " ])
  node_199 -- " <font color='black'><b>далее</b></font> " ----> node_200
  node_201["   💎 1   "]
  node_199 -- " <font color='black'><b>далее</b></font> " ----> node_201
  node_202{{"   🔄 ЦИКЛ: do-while   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_202
  class node_202 logic_style
  node_203["   💎 false   "]
  node_202 -- " <font color='black'><b>далее</b></font> " ----> node_203
  node_204["   📂 БЛОК КОДА { }   " ]
  node_202 -- " <font color='black'><b>далее</b></font> " ----> node_204
  node_205(["   🚀 ВЫЗОВ: print()   " ])
  node_204 -- " <font color='black'><b>далее</b></font> " ----> node_205
  class node_205 func_style
  node_206["   💎 хотя бы раз   "]
  node_205 -- " <font color='black'><b>далее</b></font> " ----> node_206
  node_207{{"   ♻️ ЦИКЛ: for (i)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_207
  class node_207 logic_style
  node_208["   📏 ДИАПАЗОН (..)   " ]
  node_207 -- " <font color='black'><b>далее</b></font> " ----> node_208
  class node_208 op_style
  node_209["   💎 0   "]
  node_208 -- " <font color='black'><b>далее</b></font> " ----> node_209
  node_210["   💎 10   "]
  node_208 -- " <font color='black'><b>далее</b></font> " ----> node_210
  node_211["   📂 БЛОК КОДА { }   " ]
  node_207 -- " <font color='black'><b>далее</b></font> " ----> node_211
  node_212(["   🚀 ВЫЗОВ: print()   " ])
  node_211 -- " <font color='black'><b>далее</b></font> " ----> node_212
  class node_212 func_style
  node_213(["   🔍 i   " ])
  node_212 -- " <font color='black'><b>далее</b></font> " ----> node_213
  node_214{{"   ♻️ ЦИКЛ: for (i)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_214
  class node_214 logic_style
  node_215["   📏 ДИАПАЗОН (..)   " ]
  node_214 -- " <font color='black'><b>далее</b></font> " ----> node_215
  class node_215 op_style
  node_216["   💎 0   "]
  node_215 -- " <font color='black'><b>далее</b></font> " ----> node_216
  node_217["   💎 100   "]
  node_215 -- " <font color='black'><b>далее</b></font> " ----> node_217
  node_218["   💎 10   "]
  node_214 -- " <font color='black'><b>далее</b></font> " ----> node_218
  node_219["   📂 БЛОК КОДА { }   " ]
  node_214 -- " <font color='black'><b>далее</b></font> " ----> node_219
  node_220(["   🚀 ВЫЗОВ: print()   " ])
  node_219 -- " <font color='black'><b>далее</b></font> " ----> node_220
  class node_220 func_style
  node_221(["   🔍 i   " ])
  node_220 -- " <font color='black'><b>далее</b></font> " ----> node_221
  node_222{{"   ♻️ ЦИКЛ: for (i)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_222
  class node_222 logic_style
  node_223["   📏 ДИАПАЗОН (..)   " ]
  node_222 -- " <font color='black'><b>далее</b></font> " ----> node_223
  class node_223 op_style
  node_224["   💎 0   "]
  node_223 -- " <font color='black'><b>далее</b></font> " ----> node_224
  node_225(["   🔍 n   " ])
  node_223 -- " <font color='black'><b>далее</b></font> " ----> node_225
  node_226["   💎 10   "]
  node_222 -- " <font color='black'><b>далее</b></font> " ----> node_226
  node_227["   📂 БЛОК КОДА { }   " ]
  node_222 -- " <font color='black'><b>далее</b></font> " ----> node_227
  node_228(["   🚀 ВЫЗОВ: print()   " ])
  node_227 -- " <font color='black'><b>далее</b></font> " ----> node_228
  class node_228 func_style
  node_229(["   🔍 i   " ])
  node_228 -- " <font color='black'><b>далее</b></font> " ----> node_229
  node_230{{"   ♻️ ЦИКЛ: for (item)   " }}
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_230
  class node_230 logic_style
  node_231(["   🔍 items   " ])
  node_230 -- " <font color='black'><b>далее</b></font> " ----> node_231
  node_232["   📂 БЛОК КОДА { }   " ]
  node_230 -- " <font color='black'><b>далее</b></font> " ----> node_232
  node_233(["   🚀 ВЫЗОВ: print()   " ])
  node_232 -- " <font color='black'><b>далее</b></font> " ----> node_233
  class node_233 func_style
  node_234(["   🔍 item   " ])
  node_233 -- " <font color='black'><b>далее</b></font> " ----> node_234
  node_235[["   🛑 ПРЕРВАТЬ (break)   " ]]
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_235
  node_236[["   ⏭️ ПРОДОЛЖИТЬ (continue)   " ]]
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_236
  node_237(("   🔨 ФУНКЦИЯ: f
Вернет: auto   " ))
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_237
  class node_237 func_style
  node_238["   📂 БЛОК КОДА { }   " ]
  node_237 -- " <font color='black'><b>далее</b></font> " ----> node_238
  node_239[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_238 -- " <font color='black'><b>далее</b></font> " ----> node_239
  node_240["   💎 42   "]
  node_239 -- " <font color='black'><b>далее</b></font> " ----> node_240
  node_241(("   🔨 ФУНКЦИЯ: f
Вернет: auto   " ))
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_241
  class node_241 func_style
  node_242[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_241 -- " <font color='black'><b>далее</b></font> " ----> node_242
  node_243["   💎 42   "]
  node_242 -- " <font color='black'><b>далее</b></font> " ----> node_243
  node_244(("   🔨 ФУНКЦИЯ: add
Вернет: Int   " ))
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_244
  class node_244 func_style
  node_245(["   АРГ: a (Int)   " ])
  node_244 -- " <font color='black'><b>сигнатура</b></font> " ----> node_245
  node_246(["   АРГ: b (Int)   " ])
  node_244 -- " <font color='black'><b>сигнатура</b></font> " ----> node_246
  node_247["   📂 БЛОК КОДА { }   " ]
  node_244 -- " <font color='black'><b>далее</b></font> " ----> node_247
  node_248[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_247 -- " <font color='black'><b>далее</b></font> " ----> node_248
  node_249["   ➕ СЛОЖИТЬ (+)    " ]
  node_248 -- " <font color='black'><b>далее</b></font> " ----> node_249
  class node_249 op_style
  node_250(["   🔍 a   " ])
  node_249 -- " <font color='black'><b>далее</b></font> " ----> node_250
  node_251(["   🔍 b   " ])
  node_249 -- " <font color='black'><b>далее</b></font> " ----> node_251
  node_252(("   🔨 ФУНКЦИЯ: add
Вернет: Int   " ))
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_252
  class node_252 func_style
  node_253(["   АРГ: a (auto)   " ])
  node_252 -- " <font color='black'><b>сигнатура</b></font> " ----> node_253
  node_254(["   АРГ: b (auto)   " ])
  node_252 -- " <font color='black'><b>сигнатура</b></font> " ----> node_254
  node_255[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_252 -- " <font color='black'><b>далее</b></font> " ----> node_255
  node_256["   ➕ СЛОЖИТЬ (+)    " ]
  node_255 -- " <font color='black'><b>далее</b></font> " ----> node_256
  class node_256 op_style
  node_257(["   🔍 a   " ])
  node_256 -- " <font color='black'><b>далее</b></font> " ----> node_257
  node_258(["   🔍 b   " ])
  node_256 -- " <font color='black'><b>далее</b></font> " ----> node_258
  node_259(("   🔨 ФУНКЦИЯ: f
Вернет: auto   " ))
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_259
  class node_259 func_style
  node_260(["   АРГ: x (auto)   " ])
  node_259 -- " <font color='black'><b>сигнатура</b></font> " ----> node_260
  node_261["   📂 БЛОК КОДА { }   " ]
  node_259 -- " <font color='black'><b>далее</b></font> " ----> node_261
  node_262[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_261 -- " <font color='black'><b>далее</b></font> " ----> node_262
  node_263(["   🔍 x   " ])
  node_262 -- " <font color='black'><b>далее</b></font> " ----> node_263
  node_264(("   🔨 ФУНКЦИЯ: greet
Вернет: auto   " ))
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_264
  class node_264 func_style
  node_265(["   АРГ: name (auto)   " ])
  node_264 -- " <font color='black'><b>сигнатура</b></font> " ----> node_265
  node_266(["   АРГ: greeting (auto)   " ])
  node_264 -- " <font color='black'><b>сигнатура</b></font> " ----> node_266
  node_267["   💎 Hello   "]
  node_266 -- " <font color='black'><b>далее</b></font> " ----> node_267
  node_268[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_264 -- " <font color='black'><b>далее</b></font> " ----> node_268
  node_269["   ➕ СЛОЖИТЬ (+)    " ]
  node_268 -- " <font color='black'><b>далее</b></font> " ----> node_269
  class node_269 op_style
  node_270(["   🔍 greeting   " ])
  node_269 -- " <font color='black'><b>далее</b></font> " ----> node_270
  node_271(["   🔍 name   " ])
  node_269 -- " <font color='black'><b>далее</b></font> " ----> node_271
  node_272(("   🔨 ФУНКЦИЯ: sum
Вернет: auto   " ))
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_272
  class node_272 func_style
  node_273(["   АРГ: args... (auto)   " ])
  node_272 -- " <font color='black'><b>сигнатура</b></font> " ----> node_273
  node_274[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_272 -- " <font color='black'><b>далее</b></font> " ----> node_274
  node_275["   💎 0   "]
  node_274 -- " <font color='black'><b>далее</b></font> " ----> node_275
  node_276(("   🔨 ФУНКЦИЯ: complex
Вернет: auto   " ))
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_276
  class node_276 func_style
  node_277(["   АРГ: a (Int)   " ])
  node_276 -- " <font color='black'><b>сигнатура</b></font> " ----> node_277
  node_278["   💎 0   "]
  node_277 -- " <font color='black'><b>далее</b></font> " ----> node_278
  node_279(["   АРГ: others... (auto)   " ])
  node_276 -- " <font color='black'><b>сигнатура</b></font> " ----> node_279
  node_280["   📂 БЛОК КОДА { }   " ]
  node_276 -- " <font color='black'><b>далее</b></font> " ----> node_280
  node_281(("   🔨 ФУНКЦИЯ: divide
Вернет: auto   " ))
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_281
  class node_281 func_style
  node_282(["   АРГ: a (auto)   " ])
  node_281 -- " <font color='black'><b>сигнатура</b></font> " ----> node_282
  node_283(["   АРГ: b (auto)   " ])
  node_281 -- " <font color='black'><b>сигнатура</b></font> " ----> node_283
  node_284["   🚫 НЕ РАВНО (!=)    " ]
  node_281 -- " <font color='black'><b>далее</b></font> " ----> node_284
  class node_284 op_style
  node_285(["   🔍 b   " ])
  node_284 -- " <font color='black'><b>далее</b></font> " ----> node_285
  node_286["   💎 0   "]
  node_284 -- " <font color='black'><b>далее</b></font> " ----> node_286
  node_287["   📂 БЛОК КОДА { }   " ]
  node_281 -- " <font color='black'><b>далее</b></font> " ----> node_287
  node_288[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_287 -- " <font color='black'><b>далее</b></font> " ----> node_288
  node_289["   ➗ РАЗДЕЛИТЬ (/)    " ]
  node_288 -- " <font color='black'><b>далее</b></font> " ----> node_289
  class node_289 op_style
  node_290(["   🔍 a   " ])
  node_289 -- " <font color='black'><b>далее</b></font> " ----> node_290
  node_291(["   🔍 b   " ])
  node_289 -- " <font color='black'><b>далее</b></font> " ----> node_291
  node_292(("   🔨 ФУНКЦИЯ: check
Вернет: auto   " ))
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_292
  class node_292 func_style
  node_293(["   АРГ: x (auto)   " ])
  node_292 -- " <font color='black'><b>сигнатура</b></font> " ----> node_293
  node_294["   📈 БОЛЬШЕ (>)    " ]
  node_292 -- " <font color='black'><b>далее</b></font> " ----> node_294
  class node_294 op_style
  node_295(["   🔍 x   " ])
  node_294 -- " <font color='black'><b>далее</b></font> " ----> node_295
  node_296["   💎 0   "]
  node_294 -- " <font color='black'><b>далее</b></font> " ----> node_296
  node_297[/"   ↩️ ВЕРНУТЬ (return)   " /]
  node_292 -- " <font color='black'><b>далее</b></font> " ----> node_297
  node_298["   💎 Positive   "]
  node_297 -- " <font color='black'><b>далее</b></font> " ----> node_298
  node_299["   🛡️ ПОПРОБОВАТЬ (try)   " ]
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_299
  node_300["   📂 БЛОК КОДА { }   " ]
  node_299 -- " <font color='black'><b>далее</b></font> " ----> node_300
  node_301{{"   📝 ПЕРЕМЕННЫЕ (make)   " }}
  node_300 -- " <font color='black'><b>далее</b></font> " ----> node_301
  class node_301 var_style
  node_302(["   ИМЯ: x
Тип: auto   " ])
  node_301 -- " <font color='black'><b>память</b></font> " ----> node_302
  node_303(["   🚀 ВЫЗОВ: risky()   " ])
  node_302 -- " <font color='black'><b>далее</b></font> " ----> node_303
  class node_303 func_style
  node_304{"   ⚠️ ПОЙМАТЬ (catch)   " }
  node_299 -- " <font color='black'><b>ошибка</b></font> " ----> node_304
  node_305(["   🔍 err   " ])
  node_304 -- " <font color='black'><b>далее</b></font> " ----> node_305
  node_306["   📂 БЛОК КОДА { }   " ]
  node_304 -- " <font color='black'><b>далее</b></font> " ----> node_306
  node_307(["   🚀 ВЫЗОВ: print()   " ])
  node_306 -- " <font color='black'><b>далее</b></font> " ----> node_307
  class node_307 func_style
  node_308["   ➕ СЛОЖИТЬ (+)    " ]
  node_307 -- " <font color='black'><b>далее</b></font> " ----> node_308
  class node_308 op_style
  node_309["   💎 Error:    "]
  node_308 -- " <font color='black'><b>далее</b></font> " ----> node_309
  node_310(["   🔍 err   " ])
  node_308 -- " <font color='black'><b>далее</b></font> " ----> node_310
  node_311["   📂 БЛОК КОДА { }   " ]
  node_299 -- " <font color='black'><b>далее</b></font> " ----> node_311
  node_312(["   🚀 ВЫЗОВ: print()   " ])
  node_311 -- " <font color='black'><b>далее</b></font> " ----> node_312
  class node_312 func_style
  node_313["   💎 always   "]
  node_312 -- " <font color='black'><b>далее</b></font> " ----> node_313
  node_314[/"   💥 БРОСИТЬ (throw)   " /]
  node_0 -- " <font color='black'><b>далее</b></font> " ----> node_314
  node_315(["   🚀 ВЫЗОВ: Error()   " ])
  node_314 -- " <font color='black'><b>далее</b></font> " ----> node_315
  class node_315 func_style
  node_316["   💎 Error get   "]
  node_315 -- " <font color='black'><b>далее</b></font> " ----> node_316
  node_317["📦 IMPORT: math.atm"]
  class node_317 func_style
  node_318["📦 IMPORT: math.atm"]
  class node_318 func_style
  node_319(["🔹 sin"])
  node_318 -- " <font color='black'><b>объект</b></font> " ----> node_319
  node_320(["🔹 cos"])
  node_318 -- " <font color='black'><b>объект</b></font> " ----> node_320
  node_321(["🔹 pi"])
  node_318 -- " <font color='black'><b>объект</b></font> " ----> node_321
  node_322["📦 IMPORT: math.atm"]
  class node_322 func_style
  node_323(["🔹 sin ➜ s"])
  node_322 -- " <font color='black'><b>объект</b></font> " ----> node_323
  node_324(["🔹 cos ➜ c"])
  node_322 -- " <font color='black'><b>объект</b></font> " ----> node_324
  node_325(["🔹 pi ➜ PI"])
  node_322 -- " <font color='black'><b>объект</b></font> " ----> node_325
  node_326["📦 IMPORT: math.atm as m"]
  class node_326 func_style
```
