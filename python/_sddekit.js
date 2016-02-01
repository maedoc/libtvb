[
    {
        "name": "NULL", 
        "type": "constant", 
        "value": "None"
    }, 
    {
        "args": [], 
        "name": "__mingw_get_crt_info", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "short", 
            "signed": false
        }, 
        "name": "wchar_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "short", 
            "signed": false
        }, 
        "name": "wint_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "short", 
            "signed": false
        }, 
        "name": "wctype_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "name": "errno_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": true
        }, 
        "name": "__time32_t", 
        "type": "typedef"
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "name": "refcount"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": false
                }, 
                "name": "lc_codepage"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": false
                }, 
                "name": "lc_collate_cp"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesArray", 
                    "base": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 1, 
                        "name": "int", 
                        "signed": false
                    }, 
                    "count": {
                        "Klass": "ConstantExpressionNode", 
                        "errors": [], 
                        "value": 6
                    }, 
                    "errors": []
                }, 
                "name": "lc_handle"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesArray", 
                    "base": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "LC_ID"
                    }, 
                    "count": {
                        "Klass": "ConstantExpressionNode", 
                        "errors": [], 
                        "value": 6
                    }, 
                    "errors": []
                }, 
                "name": "lc_id"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesArray", 
                    "base": {
                        "Klass": "CtypesStruct", 
                        "anonymous": true, 
                        "errors": [], 
                        "members": [
                            [
                                "locale", 
                                {
                                    "Klass": "CtypesSpecial", 
                                    "errors": [], 
                                    "name": "String"
                                }
                            ], 
                            [
                                "wlocale", 
                                {
                                    "Klass": "CtypesPointer", 
                                    "destination": {
                                        "Klass": "CtypesTypedef", 
                                        "errors": [], 
                                        "name": "wchar_t"
                                    }, 
                                    "errors": [], 
                                    "qualifiers": []
                                }
                            ], 
                            [
                                "refcount", 
                                {
                                    "Klass": "CtypesPointer", 
                                    "destination": {
                                        "Klass": "CtypesSimple", 
                                        "errors": [], 
                                        "longs": 0, 
                                        "name": "int", 
                                        "signed": true
                                    }, 
                                    "errors": [], 
                                    "qualifiers": []
                                }
                            ], 
                            [
                                "wrefcount", 
                                {
                                    "Klass": "CtypesPointer", 
                                    "destination": {
                                        "Klass": "CtypesSimple", 
                                        "errors": [], 
                                        "longs": 0, 
                                        "name": "int", 
                                        "signed": true
                                    }, 
                                    "errors": [], 
                                    "qualifiers": []
                                }
                            ]
                        ], 
                        "opaque": false, 
                        "src": [
                            "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                            450
                        ], 
                        "tag": "anon_1", 
                        "variety": "struct"
                    }, 
                    "count": {
                        "Klass": "ConstantExpressionNode", 
                        "errors": [], 
                        "value": 6
                    }, 
                    "errors": []
                }, 
                "name": "lc_category"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "name": "lc_clike"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "name": "mb_cur_max"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "lconv_intl_refcount"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "lconv_num_refcount"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "lconv_mon_refcount"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesStruct", 
                        "anonymous": false, 
                        "errors": [], 
                        "members": null, 
                        "opaque": true, 
                        "src": [
                            "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                            461
                        ], 
                        "tag": "lconv", 
                        "variety": "struct"
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "lconv"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "ctype1_refcount"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "short", 
                        "signed": false
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "ctype1"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "short", 
                        "signed": false
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "pctype"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "char", 
                        "signed": false
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "pclmap"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "char", 
                        "signed": false
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "pcumap"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesStruct", 
                        "anonymous": false, 
                        "errors": [], 
                        "members": null, 
                        "opaque": true, 
                        "src": [
                            "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                            467
                        ], 
                        "tag": "__lc_time_data", 
                        "variety": "struct"
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "lc_time_curr"
            }
        ], 
        "name": "threadlocaleinfostruct", 
        "type": "struct"
    }, 
    {
        "name": "threadmbcinfostruct", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesStruct", 
                "anonymous": false, 
                "errors": [], 
                "members": null, 
                "opaque": true, 
                "src": [
                    "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                    424
                ], 
                "tag": "threadlocaleinfostruct", 
                "variety": "struct"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "name": "pthreadlocinfo", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesStruct", 
                "anonymous": false, 
                "errors": [], 
                "members": null, 
                "opaque": true, 
                "src": [
                    "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                    425
                ], 
                "tag": "threadmbcinfostruct", 
                "variety": "struct"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "name": "pthreadmbcinfo", 
        "type": "typedef"
    }, 
    {
        "name": "__lc_time_data", 
        "type": "struct"
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "pthreadlocinfo"
                }, 
                "name": "locinfo"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "pthreadmbcinfo"
                }, 
                "name": "mbcinfo"
            }
        ], 
        "name": "localeinfo_struct", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "locinfo", 
                    {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "pthreadlocinfo"
                    }
                ], 
                [
                    "mbcinfo", 
                    {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "pthreadmbcinfo"
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                428
            ], 
            "tag": "localeinfo_struct", 
            "variety": "struct"
        }, 
        "name": "_locale_tstruct", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesStruct", 
                "anonymous": false, 
                "errors": [], 
                "members": [
                    [
                        "locinfo", 
                        {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "pthreadlocinfo"
                        }
                    ], 
                    [
                        "mbcinfo", 
                        {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "pthreadmbcinfo"
                        }
                    ]
                ], 
                "opaque": false, 
                "src": [
                    "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                    428
                ], 
                "tag": "localeinfo_struct", 
                "variety": "struct"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "name": "_locale_t", 
        "type": "typedef"
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "short", 
                    "signed": false
                }, 
                "name": "wLanguage"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "short", 
                    "signed": false
                }, 
                "name": "wCountry"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "short", 
                    "signed": false
                }, 
                "name": "wCodePage"
            }
        ], 
        "name": "tagLC_ID", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "wLanguage", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "short", 
                        "signed": false
                    }
                ], 
                [
                    "wCountry", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "short", 
                        "signed": false
                    }
                ], 
                [
                    "wCodePage", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "short", 
                        "signed": false
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                435
            ], 
            "tag": "tagLC_ID", 
            "variety": "struct"
        }, 
        "name": "LC_ID", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesStruct", 
                "anonymous": false, 
                "errors": [], 
                "members": [
                    [
                        "wLanguage", 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "short", 
                            "signed": false
                        }
                    ], 
                    [
                        "wCountry", 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "short", 
                            "signed": false
                        }
                    ], 
                    [
                        "wCodePage", 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "short", 
                            "signed": false
                        }
                    ]
                ], 
                "opaque": false, 
                "src": [
                    "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                    435
                ], 
                "tag": "tagLC_ID", 
                "variety": "struct"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "name": "LPLC_ID", 
        "type": "typedef"
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesSpecial", 
                    "errors": [], 
                    "name": "String"
                }, 
                "name": "locale"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "wchar_t"
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "wlocale"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "refcount"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "wrefcount"
            }
        ], 
        "name": "anon_1", 
        "type": "struct"
    }, 
    {
        "name": "lconv", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "refcount", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }
                ], 
                [
                    "lc_codepage", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": false
                    }
                ], 
                [
                    "lc_collate_cp", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": false
                    }
                ], 
                [
                    "lc_handle", 
                    {
                        "Klass": "CtypesArray", 
                        "base": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 1, 
                            "name": "int", 
                            "signed": false
                        }, 
                        "count": {
                            "Klass": "ConstantExpressionNode", 
                            "errors": [], 
                            "value": 6
                        }, 
                        "errors": []
                    }
                ], 
                [
                    "lc_id", 
                    {
                        "Klass": "CtypesArray", 
                        "base": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "LC_ID"
                        }, 
                        "count": {
                            "Klass": "ConstantExpressionNode", 
                            "errors": [], 
                            "value": 6
                        }, 
                        "errors": []
                    }
                ], 
                [
                    "lc_category", 
                    {
                        "Klass": "CtypesArray", 
                        "base": {
                            "Klass": "CtypesStruct", 
                            "anonymous": true, 
                            "errors": [], 
                            "members": [
                                [
                                    "locale", 
                                    {
                                        "Klass": "CtypesSpecial", 
                                        "errors": [], 
                                        "name": "String"
                                    }
                                ], 
                                [
                                    "wlocale", 
                                    {
                                        "Klass": "CtypesPointer", 
                                        "destination": {
                                            "Klass": "CtypesTypedef", 
                                            "errors": [], 
                                            "name": "wchar_t"
                                        }, 
                                        "errors": [], 
                                        "qualifiers": []
                                    }
                                ], 
                                [
                                    "refcount", 
                                    {
                                        "Klass": "CtypesPointer", 
                                        "destination": {
                                            "Klass": "CtypesSimple", 
                                            "errors": [], 
                                            "longs": 0, 
                                            "name": "int", 
                                            "signed": true
                                        }, 
                                        "errors": [], 
                                        "qualifiers": []
                                    }
                                ], 
                                [
                                    "wrefcount", 
                                    {
                                        "Klass": "CtypesPointer", 
                                        "destination": {
                                            "Klass": "CtypesSimple", 
                                            "errors": [], 
                                            "longs": 0, 
                                            "name": "int", 
                                            "signed": true
                                        }, 
                                        "errors": [], 
                                        "qualifiers": []
                                    }
                                ]
                            ], 
                            "opaque": false, 
                            "src": [
                                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                                450
                            ], 
                            "tag": "anon_1", 
                            "variety": "struct"
                        }, 
                        "count": {
                            "Klass": "ConstantExpressionNode", 
                            "errors": [], 
                            "value": 6
                        }, 
                        "errors": []
                    }
                ], 
                [
                    "lc_clike", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }
                ], 
                [
                    "mb_cur_max", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }
                ], 
                [
                    "lconv_intl_refcount", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "int", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "lconv_num_refcount", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "int", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "lconv_mon_refcount", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "int", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "lconv", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesStruct", 
                            "anonymous": false, 
                            "errors": [], 
                            "members": null, 
                            "opaque": true, 
                            "src": [
                                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                                461
                            ], 
                            "tag": "lconv", 
                            "variety": "struct"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "ctype1_refcount", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "int", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "ctype1", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "short", 
                            "signed": false
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "pctype", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "short", 
                            "signed": false
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "pclmap", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "char", 
                            "signed": false
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "pcumap", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "char", 
                            "signed": false
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "lc_time_curr", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesStruct", 
                            "anonymous": false, 
                            "errors": [], 
                            "members": null, 
                            "opaque": true, 
                            "src": [
                                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                                467
                            ], 
                            "tag": "__lc_time_data", 
                            "variety": "struct"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                444
            ], 
            "tag": "threadlocaleinfostruct", 
            "variety": "struct"
        }, 
        "name": "threadlocinfo", 
        "type": "typedef"
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesSpecial", 
                    "errors": [], 
                    "name": "String"
                }, 
                "name": "_ptr"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "name": "_cnt"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSpecial", 
                    "errors": [], 
                    "name": "String"
                }, 
                "name": "_base"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "name": "_flag"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "name": "_file"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "name": "_charbuf"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "name": "_bufsiz"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSpecial", 
                    "errors": [], 
                    "name": "String"
                }, 
                "name": "_tmpfname"
            }
        ], 
        "name": "_iobuf", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": null, 
            "opaque": true, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/stdio.h", 
                36
            ], 
            "tag": "_iobuf", 
            "variety": "struct"
        }, 
        "name": "FILE", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": true
        }, 
        "name": "_off_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": true
        }, 
        "name": "off32_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "off32_t"
        }, 
        "name": "off_t", 
        "type": "typedef"
    }, 
    {
        "args": [], 
        "name": "__iob_func", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "FILE"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Src", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Format", 
                "name": "String"
            }
        ], 
        "name": "__mingw_sscanf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Format", 
                "name": "String"
            }
        ], 
        "name": "__mingw_scanf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Format", 
                "name": "String"
            }
        ], 
        "name": "__mingw_fscanf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "", 
                "name": "String"
            }
        ], 
        "name": "__mingw_printf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "", 
                "name": "String"
            }
        ], 
        "name": "__mingw_fprintf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "", 
                "name": "String"
            }
        ], 
        "name": "__mingw_sprintf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "char", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "", 
                "name": "String"
            }
        ], 
        "name": "__mingw_asprintf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Format", 
                "name": "String"
            }
        ], 
        "name": "fprintf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Format", 
                "name": "String"
            }
        ], 
        "name": "printf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Dest", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Format", 
                "name": "String"
            }
        ], 
        "name": "sprintf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Format", 
                "name": "String"
            }
        ], 
        "name": "fscanf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Format", 
                "name": "String"
            }
        ], 
        "name": "scanf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Src", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Format", 
                "name": "String"
            }
        ], 
        "name": "sscanf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "_filbuf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Ch", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "_flsbuf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Filename", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Mode", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_ShFlag", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_fsopen", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "FILE"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "clearerr", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "fclose", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "_fcloseall", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_FileHandle", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Mode", 
                "name": "String"
            }
        ], 
        "name": "_fdopen", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "FILE"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "feof", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "ferror", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "fflush", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "fgetc", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "_fgetchar", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Buf", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_MaxCount", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "fgets", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "_fileno", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_DirName", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_FilePrefix", 
                "name": "String"
            }
        ], 
        "name": "_tempnam", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "_flushall", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Filename", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Mode", 
                "name": "String"
            }
        ], 
        "name": "fopen", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "FILE"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "filename", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "mode", 
                "name": "String"
            }
        ], 
        "name": "fopen64", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "FILE"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Ch", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "fputc", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Ch", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_fputchar", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "fputs", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Filename", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Mode", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "freopen", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "FILE"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Offset", 
                "longs": 1, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Origin", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "fseek", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "stream", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "offset", 
                "name": "_off_t"
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "whence", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "fseeko", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "ftell", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "stream", 
                "qualifiers": []
            }
        ], 
        "name": "ftello", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "_off_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "getc", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "getchar", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "_getmaxstdio", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Buffer", 
                "name": "String"
            }
        ], 
        "name": "gets", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "_getw", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_ErrMsg", 
                "name": "String"
            }
        ], 
        "name": "perror", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "_pclose", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Command", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Mode", 
                "name": "String"
            }
        ], 
        "name": "_popen", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "FILE"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Ch", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "putc", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Ch", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "putchar", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }
        ], 
        "name": "puts", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Word", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "_putw", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Filename", 
                "name": "String"
            }
        ], 
        "name": "remove", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_OldFilename", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_NewFilename", 
                "name": "String"
            }
        ], 
        "name": "rename", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Filename", 
                "name": "String"
            }
        ], 
        "name": "_unlink", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Filename", 
                "name": "String"
            }
        ], 
        "name": "unlink", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "rewind", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "_rmtmp", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Buffer", 
                "name": "String"
            }
        ], 
        "name": "setbuf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Max", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_setmaxstdio", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Format", 
                "longs": 0, 
                "name": "int", 
                "signed": false
            }
        ], 
        "name": "_set_output_format", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": false
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "_get_output_format", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": false
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Format", 
                "name": "String"
            }
        ], 
        "name": "_scprintf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [], 
        "name": "tmpfile", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "FILE"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Buffer", 
                "name": "String"
            }
        ], 
        "name": "tmpnam", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Ch", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "ungetc", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "name": "__retval", 
        "type": "variable"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Value", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_set_printf_count_output", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "_get_printf_count_output", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Src", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Format", 
                "qualifiers": []
            }
        ], 
        "name": "__mingw_swscanf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Format", 
                "qualifiers": []
            }
        ], 
        "name": "__mingw_wscanf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Format", 
                "qualifiers": []
            }
        ], 
        "name": "__mingw_fwscanf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Format", 
                "qualifiers": []
            }
        ], 
        "name": "__mingw_fwprintf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Format", 
                "qualifiers": []
            }
        ], 
        "name": "__mingw_wprintf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "", 
                "qualifiers": []
            }
        ], 
        "name": "__mingw_swprintf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Format", 
                "qualifiers": []
            }
        ], 
        "name": "fwscanf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Src", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Format", 
                "qualifiers": []
            }
        ], 
        "name": "swscanf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Format", 
                "qualifiers": []
            }
        ], 
        "name": "wscanf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Format", 
                "qualifiers": []
            }
        ], 
        "name": "fwprintf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Format", 
                "qualifiers": []
            }
        ], 
        "name": "wprintf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Filename", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Mode", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_ShFlag", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_wfsopen", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "FILE"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "fgetwc", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "wint_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "_fgetwchar", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "wint_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Ch", 
                "name": "wchar_t"
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "fputwc", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "wint_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Ch", 
                "name": "wchar_t"
            }
        ], 
        "name": "_fputwchar", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "wint_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "getwc", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "wint_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "getwchar", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "wint_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Ch", 
                "name": "wchar_t"
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "putwc", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "wint_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Ch", 
                "name": "wchar_t"
            }
        ], 
        "name": "putwchar", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "wint_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Ch", 
                "name": "wint_t"
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "ungetwc", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "wint_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Dst", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_SizeInWords", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "fgetws", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "fputws", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_String", 
                "qualifiers": []
            }
        ], 
        "name": "_getws", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }
        ], 
        "name": "_putws", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Format", 
                "qualifiers": []
            }
        ], 
        "name": "_scwprintf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "name": "r", 
        "type": "variable"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Dest", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Format", 
                "qualifiers": []
            }
        ], 
        "name": "_swprintf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": true
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "name": "__retval", 
        "type": "variable"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Directory", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_FilePrefix", 
                "qualifiers": []
            }
        ], 
        "name": "_wtempnam", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_FileHandle", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Mode", 
                "qualifiers": []
            }
        ], 
        "name": "_wfdopen", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "FILE"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Filename", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Mode", 
                "qualifiers": []
            }
        ], 
        "name": "_wfopen", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "FILE"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Filename", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Mode", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_OldFile", 
                "qualifiers": []
            }
        ], 
        "name": "_wfreopen", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "FILE"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_ErrMsg", 
                "qualifiers": []
            }
        ], 
        "name": "_wperror", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Command", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Mode", 
                "qualifiers": []
            }
        ], 
        "name": "_wpopen", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "FILE"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Filename", 
                "qualifiers": []
            }
        ], 
        "name": "_wremove", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Buffer", 
                "qualifiers": []
            }
        ], 
        "name": "_wtmpnam", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "_fgetwc_nolock", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "wint_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Ch", 
                "name": "wchar_t"
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "_fputwc_nolock", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "wint_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Ch", 
                "name": "wint_t"
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "_ungetwc_nolock", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "wint_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "_lock_file", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "_unlock_file", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "_fclose_nolock", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "_fflush_nolock", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Offset", 
                "longs": 1, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Origin", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_fseek_nolock", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "_ftell_nolock", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Ch", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "_ungetc_nolock", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Directory", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_FilePrefix", 
                "name": "String"
            }
        ], 
        "name": "tempnam", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "fcloseall", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_FileHandle", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Format", 
                "name": "String"
            }
        ], 
        "name": "fdopen", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "FILE"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "fgetchar", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "fileno", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "flushall", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Ch", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "fputchar", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "getw", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Ch", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "_File", 
                "qualifiers": []
            }
        ], 
        "name": "putw", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "rmtmp", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "void", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "ptr", 
                "qualifiers": []
            }
        ], 
        "name": "__mingw_str_free", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "ctype": {
            "Klass": "CtypesFunction", 
            "argtypes": [], 
            "errors": [], 
            "restype": {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            "variadic": false
        }, 
        "name": "_onexit_t", 
        "type": "typedef"
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "name": "quot"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "name": "rem"
            }
        ], 
        "name": "_div_t", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "quot", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }
                ], 
                [
                    "rem", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/stdlib.h", 
                50
            ], 
            "tag": "_div_t", 
            "variety": "struct"
        }, 
        "name": "div_t", 
        "type": "typedef"
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 1, 
                    "name": "int", 
                    "signed": true
                }, 
                "name": "quot"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 1, 
                    "name": "int", 
                    "signed": true
                }, 
                "name": "rem"
            }
        ], 
        "name": "_ldiv_t", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "quot", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 1, 
                        "name": "int", 
                        "signed": true
                    }
                ], 
                [
                    "rem", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 1, 
                        "name": "int", 
                        "signed": true
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/stdlib.h", 
                55
            ], 
            "tag": "_ldiv_t", 
            "variety": "struct"
        }, 
        "name": "ldiv_t", 
        "type": "typedef"
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesArray", 
                    "base": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "char", 
                        "signed": false
                    }, 
                    "count": {
                        "Klass": "ConstantExpressionNode", 
                        "errors": [], 
                        "value": 10
                    }, 
                    "errors": []
                }, 
                "name": "ld"
            }
        ], 
        "name": "anon_2", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": true, 
            "errors": [], 
            "members": [
                [
                    "ld", 
                    {
                        "Klass": "CtypesArray", 
                        "base": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "char", 
                            "signed": false
                        }, 
                        "count": {
                            "Klass": "ConstantExpressionNode", 
                            "errors": [], 
                            "value": 10
                        }, 
                        "errors": []
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/stdlib.h", 
                65
            ], 
            "tag": "anon_2", 
            "variety": "struct"
        }, 
        "name": "_LDOUBLE", 
        "type": "typedef"
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "name": "x"
            }
        ], 
        "name": "anon_3", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": true, 
            "errors": [], 
            "members": [
                [
                    "x", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/stdlib.h", 
                72
            ], 
            "tag": "anon_3", 
            "variety": "struct"
        }, 
        "name": "_CRT_DOUBLE", 
        "type": "typedef"
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "float", 
                    "signed": true
                }, 
                "name": "f"
            }
        ], 
        "name": "anon_4", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": true, 
            "errors": [], 
            "members": [
                [
                    "f", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "float", 
                        "signed": true
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/stdlib.h", 
                76
            ], 
            "tag": "anon_4", 
            "variety": "struct"
        }, 
        "name": "_CRT_FLOAT", 
        "type": "typedef"
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesArray", 
                    "base": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "char", 
                        "signed": false
                    }, 
                    "count": {
                        "Klass": "ConstantExpressionNode", 
                        "errors": [], 
                        "value": 12
                    }, 
                    "errors": []
                }, 
                "name": "ld12"
            }
        ], 
        "name": "anon_6", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": true, 
            "errors": [], 
            "members": [
                [
                    "ld12", 
                    {
                        "Klass": "CtypesArray", 
                        "base": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "char", 
                            "signed": false
                        }, 
                        "count": {
                            "Klass": "ConstantExpressionNode", 
                            "errors": [], 
                            "value": 12
                        }, 
                        "errors": []
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/stdlib.h", 
                90
            ], 
            "tag": "anon_6", 
            "variety": "struct"
        }, 
        "name": "_LDBL12", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "name": "__imp___mb_cur_max", 
        "type": "variable"
    }, 
    {
        "ctype": {
            "Klass": "CtypesFunction", 
            "argtypes": [], 
            "errors": [], 
            "restype": {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "longs": 0, 
                "name": "void", 
                "signed": true
            }, 
            "variadic": false
        }, 
        "name": "_purecall_handler", 
        "type": "typedef"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Handler", 
                "name": "_purecall_handler"
            }
        ], 
        "name": "_set_purecall_handler", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "_purecall_handler"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "_get_purecall_handler", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "_purecall_handler"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "_errno", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Value", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_set_errno", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "errno_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "_Value", 
                "qualifiers": []
            }
        ], 
        "name": "_get_errno", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "errno_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "__doserrno", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "longs": 1, 
                "name": "int", 
                "signed": false
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Value", 
                "longs": 1, 
                "name": "int", 
                "signed": false
            }
        ], 
        "name": "_set_doserrno", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "errno_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 1, 
                    "name": "int", 
                    "signed": false
                }, 
                "errors": [], 
                "identifier": "_Value", 
                "qualifiers": []
            }
        ], 
        "name": "_get_doserrno", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "errno_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "ctype": {
            "Klass": "CtypesArray", 
            "base": {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "char", 
                    "signed": true
                }, 
                "errors": [], 
                "qualifiers": []
            }, 
            "count": {
                "Klass": "ConstantExpressionNode", 
                "errors": [], 
                "value": 1
            }, 
            "errors": []
        }, 
        "name": "_sys_errlist", 
        "type": "variable"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "name": "_sys_nerr", 
        "type": "variable"
    }, 
    {
        "ctype": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "name": "__imp___argc", 
        "type": "variable"
    }, 
    {
        "ctype": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "char", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "qualifiers": []
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "name": "__imp___argv", 
        "type": "variable"
    }, 
    {
        "ctype": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "wchar_t"
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "qualifiers": []
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "name": "__imp___wargv", 
        "type": "variable"
    }, 
    {
        "ctype": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "char", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "qualifiers": []
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "name": "__imp__environ", 
        "type": "variable"
    }, 
    {
        "ctype": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "wchar_t"
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "qualifiers": []
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "name": "__imp__wenviron", 
        "type": "variable"
    }, 
    {
        "ctype": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "char", 
                    "signed": true
                }, 
                "errors": [], 
                "qualifiers": []
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "name": "__imp__pgmptr", 
        "type": "variable"
    }, 
    {
        "ctype": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "qualifiers": []
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "name": "__imp__wpgmptr", 
        "type": "variable"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "char", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "_Value", 
                "qualifiers": []
            }
        ], 
        "name": "_get_pgmptr", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "errno_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "wchar_t"
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "_Value", 
                "qualifiers": []
            }
        ], 
        "name": "_get_wpgmptr", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "errno_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "ctype": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "name": "__imp__fmode", 
        "type": "variable"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Mode", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_set_fmode", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "errno_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "_PMode", 
                "qualifiers": []
            }
        ], 
        "name": "_get_fmode", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "errno_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "ctype": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "longs": 0, 
                "name": "int", 
                "signed": false
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "name": "__imp__osplatform", 
        "type": "variable"
    }, 
    {
        "ctype": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "longs": 0, 
                "name": "int", 
                "signed": false
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "name": "__imp__osver", 
        "type": "variable"
    }, 
    {
        "ctype": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "longs": 0, 
                "name": "int", 
                "signed": false
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "name": "__imp__winver", 
        "type": "variable"
    }, 
    {
        "ctype": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "longs": 0, 
                "name": "int", 
                "signed": false
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "name": "__imp__winmajor", 
        "type": "variable"
    }, 
    {
        "ctype": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "longs": 0, 
                "name": "int", 
                "signed": false
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "name": "__imp__winminor", 
        "type": "variable"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": false
                }, 
                "errors": [], 
                "identifier": "_Value", 
                "qualifiers": []
            }
        ], 
        "name": "_get_osplatform", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "errno_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": false
                }, 
                "errors": [], 
                "identifier": "_Value", 
                "qualifiers": []
            }
        ], 
        "name": "_get_osver", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "errno_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": false
                }, 
                "errors": [], 
                "identifier": "_Value", 
                "qualifiers": []
            }
        ], 
        "name": "_get_winver", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "errno_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": false
                }, 
                "errors": [], 
                "identifier": "_Value", 
                "qualifiers": []
            }
        ], 
        "name": "_get_winmajor", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "errno_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": false
                }, 
                "errors": [], 
                "identifier": "_Value", 
                "qualifiers": []
            }
        ], 
        "name": "_get_winminor", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "errno_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Code", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "exit", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Code", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_exit", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_Exit", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "abort", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Flags", 
                "longs": 0, 
                "name": "int", 
                "signed": false
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Mask", 
                "longs": 0, 
                "name": "int", 
                "signed": false
            }
        ], 
        "name": "_set_abort_behavior", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": false
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "abs", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 1, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "labs", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesFunction", 
                "argtypes": [], 
                "errors": [], 
                "restype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "void", 
                    "signed": true
                }, 
                "variadic": false
            }
        ], 
        "name": "atexit", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_String", 
                "name": "String"
            }
        ], 
        "name": "atof", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_String", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_atof_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }
        ], 
        "name": "atoi", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_atoi_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }
        ], 
        "name": "atol", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_atol_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Short", 
                "longs": 0, 
                "name": "short", 
                "signed": false
            }
        ], 
        "name": "_byteswap_ushort", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "short", 
            "signed": false
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Long", 
                "longs": 1, 
                "name": "int", 
                "signed": false
            }
        ], 
        "name": "_byteswap_ulong", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": false
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Numerator", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Denominator", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "div", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "div_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_VarName", 
                "name": "String"
            }
        ], 
        "name": "getenv", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Value", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Dest", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Radix", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_itoa", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Numerator", 
                "longs": 1, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Denominator", 
                "longs": 1, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "ldiv", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "ldiv_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Value", 
                "longs": 1, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Dest", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Radix", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_ltoa", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "template_name", 
                "name": "String"
            }
        ], 
        "name": "mkstemp", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "rand", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Mode", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_set_error_mode", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Seed", 
                "longs": 0, 
                "name": "int", 
                "signed": false
            }
        ], 
        "name": "srand", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "char", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "_EndPtr", 
                "qualifiers": []
            }
        ], 
        "name": "strtod", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "nptr", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "char", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "endptr", 
                "qualifiers": []
            }
        ], 
        "name": "strtof", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "char", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "", 
                "qualifiers": []
            }
        ], 
        "name": "__strtod", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "char", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "", 
                "qualifiers": []
            }
        ], 
        "name": "__mingw_strtof", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "char", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "", 
                "qualifiers": []
            }
        ], 
        "name": "__mingw_strtod", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "char", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "_EndPtr", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_strtod_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "char", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "_EndPtr", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Radix", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "strtol", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "char", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "_EndPtr", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Radix", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_strtol_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "char", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "_EndPtr", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Radix", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "strtoul", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": false
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "char", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "_EndPtr", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Radix", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_strtoul_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": false
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Command", 
                "name": "String"
            }
        ], 
        "name": "system", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Value", 
                "longs": 1, 
                "name": "int", 
                "signed": false
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Dest", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Radix", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_ultoa", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_MbCh", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_WCh", 
                "name": "wchar_t"
            }
        ], 
        "name": "wctomb", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_MbCh", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_WCh", 
                "name": "wchar_t"
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_wctomb_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "void", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "_Memory", 
                "qualifiers": []
            }
        ], 
        "name": "free", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "void", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "_Memory", 
                "qualifiers": []
            }
        ], 
        "name": "_aligned_free", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Value", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Dest", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Radix", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_itow", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Value", 
                "longs": 1, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Dest", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Radix", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_ltow", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Value", 
                "longs": 1, 
                "name": "int", 
                "signed": false
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Dest", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Radix", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_ultow", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "wchar_t"
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "_EndPtr", 
                "qualifiers": []
            }
        ], 
        "name": "__mingw_wcstod", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "nptr", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "wchar_t"
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "endptr", 
                "qualifiers": []
            }
        ], 
        "name": "__mingw_wcstof", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "wchar_t"
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "_EndPtr", 
                "qualifiers": []
            }
        ], 
        "name": "wcstod", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "nptr", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "wchar_t"
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "endptr", 
                "qualifiers": []
            }
        ], 
        "name": "wcstof", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "wchar_t"
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "_EndPtr", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_wcstod_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "wchar_t"
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "_EndPtr", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Radix", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "wcstol", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "wchar_t"
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "_EndPtr", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Radix", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_wcstol_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "wchar_t"
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "_EndPtr", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Radix", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "wcstoul", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": false
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "wchar_t"
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "_EndPtr", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Radix", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_wcstoul_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": false
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_VarName", 
                "qualifiers": []
            }
        ], 
        "name": "_wgetenv", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Command", 
                "qualifiers": []
            }
        ], 
        "name": "_wsystem", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }
        ], 
        "name": "_wtof", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_wtof_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }
        ], 
        "name": "_wtoi", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_wtoi_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }
        ], 
        "name": "_wtol", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_wtol_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_EnvString", 
                "name": "String"
            }
        ], 
        "name": "_putenv", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_EnvString", 
                "qualifiers": []
            }
        ], 
        "name": "_wputenv", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Val", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_NumOfDigits", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "_PtDec", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "_PtSign", 
                "qualifiers": []
            }
        ], 
        "name": "_ecvt", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Val", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_NumOfDec", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "_PtDec", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "_PtSign", 
                "qualifiers": []
            }
        ], 
        "name": "_fcvt", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Val", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_NumOfDigits", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_DstBuf", 
                "name": "String"
            }
        ], 
        "name": "_gcvt", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "_CRT_DOUBLE"
                }, 
                "errors": [], 
                "identifier": "_Result", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }
        ], 
        "name": "_atodbl", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "_LDOUBLE"
                }, 
                "errors": [], 
                "identifier": "_Result", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }
        ], 
        "name": "_atoldbl", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "_CRT_FLOAT"
                }, 
                "errors": [], 
                "identifier": "_Result", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }
        ], 
        "name": "_atoflt", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "_CRT_DOUBLE"
                }, 
                "errors": [], 
                "identifier": "_Result", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_atodbl_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "_LDOUBLE"
                }, 
                "errors": [], 
                "identifier": "_Result", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_atoldbl_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "_CRT_FLOAT"
                }, 
                "errors": [], 
                "identifier": "_Result", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_atoflt_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 1, 
                "name": "int", 
                "signed": false
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_lrotl", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": false
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 1, 
                "name": "int", 
                "signed": false
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_lrotr", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": false
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Path", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Drive", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Dir", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Filename", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Ext", 
                "name": "String"
            }
        ], 
        "name": "_makepath", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Func", 
                "name": "_onexit_t"
            }
        ], 
        "name": "_onexit", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "_onexit_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Val", 
                "longs": 0, 
                "name": "int", 
                "signed": false
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Shift", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_rotr", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": false
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Val", 
                "longs": 0, 
                "name": "int", 
                "signed": false
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Shift", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_rotl", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": false
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Filename", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_EnvVar", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_ResultPath", 
                "name": "String"
            }
        ], 
        "name": "_searchenv", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_FullPath", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Drive", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Dir", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Filename", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Ext", 
                "name": "String"
            }
        ], 
        "name": "_splitpath", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Buf1", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Buf2", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_SizeInBytes", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_swab", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_ResultPath", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Drive", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Dir", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Filename", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Ext", 
                "qualifiers": []
            }
        ], 
        "name": "_wmakepath", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Filename", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_EnvVar", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_ResultPath", 
                "qualifiers": []
            }
        ], 
        "name": "_wsearchenv", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_FullPath", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Drive", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Dir", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Filename", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Ext", 
                "qualifiers": []
            }
        ], 
        "name": "_wsplitpath", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Frequency", 
                "longs": 0, 
                "name": "int", 
                "signed": false
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Duration", 
                "longs": 0, 
                "name": "int", 
                "signed": false
            }
        ], 
        "name": "_beep", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Mode", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_seterrormode", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Duration", 
                "longs": 1, 
                "name": "int", 
                "signed": false
            }
        ], 
        "name": "_sleep", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Val", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_NumOfDigits", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "_PtDec", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "_PtSign", 
                "qualifiers": []
            }
        ], 
        "name": "ecvt", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Val", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_NumOfDec", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "_PtDec", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "_PtSign", 
                "qualifiers": []
            }
        ], 
        "name": "fcvt", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Val", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_NumOfDigits", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_DstBuf", 
                "name": "String"
            }
        ], 
        "name": "gcvt", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Val", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_DstBuf", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Radix", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "itoa", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Val", 
                "longs": 1, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_DstBuf", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Radix", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "ltoa", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_EnvString", 
                "name": "String"
            }
        ], 
        "name": "putenv", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Buf1", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Buf2", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_SizeInBytes", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "swab", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Val", 
                "longs": 1, 
                "name": "int", 
                "signed": false
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Dstbuf", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Radix", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "ultoa", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Func", 
                "name": "_onexit_t"
            }
        ], 
        "name": "onexit", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "_onexit_t"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "name": "_useflag", 
        "type": "variable"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": false
        }, 
        "name": "_amblksiz", 
        "type": "variable"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "void", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "_Memory", 
                "qualifiers": []
            }
        ], 
        "name": "__mingw_aligned_free", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "_resetstkoflw", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_NewValue", 
                "longs": 1, 
                "name": "int", 
                "signed": false
            }
        ], 
        "name": "_set_malloc_crt_max_wait", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": false
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "_heapchk", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "_heapmin", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Fill", 
                "longs": 0, 
                "name": "int", 
                "signed": false
            }
        ], 
        "name": "_heapset", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": false
        }, 
        "name": "_Marker", 
        "type": "variable"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Val", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_strset", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Val", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_strset_l", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Dest", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Source", 
                "name": "String"
            }
        ], 
        "name": "strcpy", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Dest", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Source", 
                "name": "String"
            }
        ], 
        "name": "strcat", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str1", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str2", 
                "name": "String"
            }
        ], 
        "name": "strcmp", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Src", 
                "name": "String"
            }
        ], 
        "name": "_strdup", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Val", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "strchr", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str1", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str2", 
                "name": "String"
            }
        ], 
        "name": "_stricmp", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str1", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str2", 
                "name": "String"
            }
        ], 
        "name": "_strcmpi", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str1", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str2", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_stricmp_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str1", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str2", 
                "name": "String"
            }
        ], 
        "name": "strcoll", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str1", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str2", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_strcoll_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str1", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str2", 
                "name": "String"
            }
        ], 
        "name": "_stricoll", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str1", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str2", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_stricoll_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_ErrMsg", 
                "name": "String"
            }
        ], 
        "name": "_strerror", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "strerror", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_String", 
                "name": "String"
            }
        ], 
        "name": "_strlwr", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_String", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "strlwr_l", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Control", 
                "name": "String"
            }
        ], 
        "name": "strpbrk", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Ch", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "strrchr", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }
        ], 
        "name": "_strrev", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_SubStr", 
                "name": "String"
            }
        ], 
        "name": "strstr", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Delim", 
                "name": "String"
            }
        ], 
        "name": "strtok", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Delim", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "char", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "__last", 
                "qualifiers": []
            }
        ], 
        "name": "strtok_r", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_String", 
                "name": "String"
            }
        ], 
        "name": "_strupr", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_String", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_strupr_l", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Src", 
                "name": "String"
            }
        ], 
        "name": "strdup", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str1", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str2", 
                "name": "String"
            }
        ], 
        "name": "strcmpi", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str1", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str2", 
                "name": "String"
            }
        ], 
        "name": "stricmp", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }
        ], 
        "name": "strlwr", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "", 
                "name": "String"
            }
        ], 
        "name": "strcasecmp", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }
        ], 
        "name": "strrev", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Val", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "strset", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "_Str", 
                "name": "String"
            }
        ], 
        "name": "strupr", 
        "return": {
            "Klass": "CtypesSpecial", 
            "errors": [], 
            "name": "String"
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }
        ], 
        "name": "_wcsdup", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Dest", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Source", 
                "qualifiers": []
            }
        ], 
        "name": "wcscat", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Ch", 
                "name": "wchar_t"
            }
        ], 
        "name": "wcschr", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str1", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str2", 
                "qualifiers": []
            }
        ], 
        "name": "wcscmp", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Dest", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Source", 
                "qualifiers": []
            }
        ], 
        "name": "wcscpy", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Control", 
                "qualifiers": []
            }
        ], 
        "name": "wcspbrk", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Ch", 
                "name": "wchar_t"
            }
        ], 
        "name": "wcsrchr", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_SubStr", 
                "qualifiers": []
            }
        ], 
        "name": "wcsstr", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Delim", 
                "qualifiers": []
            }
        ], 
        "name": "wcstok", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_ErrNum", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_wcserror", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }
        ], 
        "name": "__wcserror", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str1", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str2", 
                "qualifiers": []
            }
        ], 
        "name": "_wcsicmp", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str1", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str2", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_wcsicmp_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }
        ], 
        "name": "_wcsrev", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Val", 
                "name": "wchar_t"
            }
        ], 
        "name": "_wcsset", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_String", 
                "qualifiers": []
            }
        ], 
        "name": "_wcslwr", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_String", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_wcslwr_l", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_String", 
                "qualifiers": []
            }
        ], 
        "name": "_wcsupr", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_String", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_wcsupr_l", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str1", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str2", 
                "qualifiers": []
            }
        ], 
        "name": "wcscoll", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str1", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str2", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_wcscoll_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str1", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str2", 
                "qualifiers": []
            }
        ], 
        "name": "_wcsicoll", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str1", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str2", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Locale", 
                "name": "_locale_t"
            }
        ], 
        "name": "_wcsicoll_l", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }
        ], 
        "name": "wcsdup", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str1", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str2", 
                "qualifiers": []
            }
        ], 
        "name": "wcsicmp", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }
        ], 
        "name": "wcsrev", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "_Val", 
                "name": "wchar_t"
            }
        ], 
        "name": "wcsset", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }
        ], 
        "name": "wcslwr", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str", 
                "qualifiers": []
            }
        ], 
        "name": "wcsupr", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "wchar_t"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str1", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "wchar_t"
                }, 
                "errors": [], 
                "identifier": "_Str2", 
                "qualifiers": []
            }
        ], 
        "name": "wcsicoll", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "__threadid", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": false
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "char", 
            "signed": true
        }, 
        "name": "int8_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "char", 
            "signed": false
        }, 
        "name": "uint8_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "short", 
            "signed": true
        }, 
        "name": "int16_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "short", 
            "signed": false
        }, 
        "name": "uint16_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "name": "int32_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": false
        }, 
        "name": "uint32_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "char", 
            "signed": true
        }, 
        "name": "int_least8_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "char", 
            "signed": false
        }, 
        "name": "uint_least8_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "short", 
            "signed": true
        }, 
        "name": "int_least16_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "short", 
            "signed": false
        }, 
        "name": "uint_least16_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "name": "int_least32_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": false
        }, 
        "name": "uint_least32_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "char", 
            "signed": true
        }, 
        "name": "int_fast8_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "char", 
            "signed": false
        }, 
        "name": "uint_fast8_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "short", 
            "signed": true
        }, 
        "name": "int_fast16_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "short", 
            "signed": false
        }, 
        "name": "uint_fast16_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "name": "int_fast32_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": false
        }, 
        "name": "uint_fast32_t", 
        "type": "typedef"
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "name": "type"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSpecial", 
                    "errors": [], 
                    "name": "String"
                }, 
                "name": "name"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "name": "arg1"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "name": "arg2"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "name": "retval"
            }
        ], 
        "name": "_exception", 
        "type": "struct"
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": false
                }, 
                "name": "low"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": false
                }, 
                "name": "high"
            }
        ], 
        "name": "anon_9", 
        "type": "struct"
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "float", 
                    "signed": true
                }, 
                "name": "x"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": false
                }, 
                "name": "val"
            }
        ], 
        "name": "__mingw_flt_type_t", 
        "type": "union"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "x", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "float", 
                        "signed": true
                    }
                ], 
                [
                    "val", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": false
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/math.h", 
                127
            ], 
            "tag": "__mingw_flt_type_t", 
            "variety": "union"
        }, 
        "name": "__mingw_flt_type_t", 
        "type": "typedef"
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": false
                }, 
                "name": "low"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": false
                }, 
                "name": "high"
            }, 
            {
                "bitfield": "16", 
                "ctype": {
                    "Klass": "CtypesBitfield", 
                    "base": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }, 
                    "bitfield": {
                        "Klass": "ConstantExpressionNode", 
                        "errors": [], 
                        "value": 16
                    }, 
                    "errors": []
                }, 
                "name": "sign_exponent"
            }, 
            {
                "bitfield": "16", 
                "ctype": {
                    "Klass": "CtypesBitfield", 
                    "base": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }, 
                    "bitfield": {
                        "Klass": "ConstantExpressionNode", 
                        "errors": [], 
                        "value": 16
                    }, 
                    "errors": []
                }, 
                "name": "res1"
            }, 
            {
                "bitfield": "32", 
                "ctype": {
                    "Klass": "CtypesBitfield", 
                    "base": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }, 
                    "bitfield": {
                        "Klass": "ConstantExpressionNode", 
                        "errors": [], 
                        "value": 32
                    }, 
                    "errors": []
                }, 
                "name": "res0"
            }
        ], 
        "name": "anon_10", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "name": "__imp__HUGE", 
        "type": "variable"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "typ", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "name", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "a1", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "a2", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "rslt", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "__mingw_raise_matherr", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesFunction", 
                "argtypes": [
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesStruct", 
                            "anonymous": false, 
                            "errors": [], 
                            "members": null, 
                            "opaque": true, 
                            "src": [
                                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/math.h", 
                                178
                            ], 
                            "tag": "_exception", 
                            "variety": "struct"
                        }, 
                        "errors": [], 
                        "identifier": "", 
                        "qualifiers": []
                    }
                ], 
                "errors": [], 
                "restype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "variadic": false
            }
        ], 
        "name": "__mingw_setusermatherr", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesFunction", 
                "argtypes": [
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesStruct", 
                            "anonymous": false, 
                            "errors": [], 
                            "members": null, 
                            "opaque": true, 
                            "src": [
                                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/math.h", 
                                179
                            ], 
                            "tag": "_exception", 
                            "variety": "struct"
                        }, 
                        "errors": [], 
                        "identifier": "", 
                        "qualifiers": []
                    }
                ], 
                "errors": [], 
                "restype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "variadic": false
            }
        ], 
        "name": "__setusermatherr", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "sin", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "cos", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "tan", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "sinh", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "cosh", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "tanh", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "asin", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "acos", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "atan", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Y", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "atan2", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "exp", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "log", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "log10", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Y", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "pow", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "sqrt", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "ceil", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "floor", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "x", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "fabsf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "fabs", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Y", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "ldexp", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "_Y", 
                "qualifiers": []
            }
        ], 
        "name": "frexp", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "_Y", 
                "qualifiers": []
            }
        ], 
        "name": "modf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Y", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "fmod", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "__x", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "p_sin", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "p_cos", 
                "qualifiers": []
            }
        ], 
        "name": "sincos", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "__x", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "float", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "p_sin", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "float", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "p_cos", 
                "qualifiers": []
            }
        ], 
        "name": "sincosf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "name": "x"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "name": "y"
            }
        ], 
        "name": "_complex", 
        "type": "struct"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesStruct", 
                "anonymous": false, 
                "errors": [], 
                "identifier": "_ComplexA", 
                "members": null, 
                "opaque": true, 
                "src": [
                    "C:/TDM-GCC-64/x86_64-w64-mingw32/include/math.h", 
                    272
                ], 
                "tag": "_complex", 
                "variety": "struct"
            }
        ], 
        "name": "_cabs", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Y", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "_hypot", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "_j0", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "_j1", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Y", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "_jn", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "_y0", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "_y1", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Y", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "_yn", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesStruct", 
                    "anonymous": false, 
                    "errors": [], 
                    "members": null, 
                    "opaque": true, 
                    "src": [
                        "C:/TDM-GCC-64/x86_64-w64-mingw32/include/math.h", 
                        282
                    ], 
                    "tag": "_exception", 
                    "variety": "struct"
                }, 
                "errors": [], 
                "identifier": "", 
                "qualifiers": []
            }
        ], 
        "name": "_matherr", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "_chgsign", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Number", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Sign", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "_copysign", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "_logb", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "_nextafter", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 1, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "_scalb", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "_finite", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "_fpclass", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "_isnan", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "j0", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "j1", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "jn", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "y0", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "y1", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "yn", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "chgsign", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "finite", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "fpclass", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "name": "__INFF", 
        "type": "variable"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "name": "__QNAN", 
        "type": "variable"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "name": "float_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "name": "double_t", 
        "type": "typedef"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "__fpclassifyf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "__fpclassify", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "__isnan", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "__isnanf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "__signbit", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "__signbitf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "sinf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "cosf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "tanf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "asinf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "acosf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "atanf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "atan2f", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "sinhf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "coshf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "tanhf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "acosh", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "acoshf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "asinh", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "asinhf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "atanh", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "atanhf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "expf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "exp2", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "exp2f", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "expm1", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "expm1f", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "_Y", 
                "qualifiers": []
            }
        ], 
        "name": "frexpf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "ilogb", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "ilogbf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Y", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "ldexpf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "logf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "log10f", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "log1p", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "log1pf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "log2", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "log2f", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "logb", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "logbf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "float", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "", 
                "qualifiers": []
            }
        ], 
        "name": "modff", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "scalbn", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "scalbnf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 1, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "scalbln", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 1, 
                "name": "int", 
                "signed": true
            }
        ], 
        "name": "scalblnf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "cbrt", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "cbrtf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "hypot", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "x", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "y", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "hypotf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Y", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "powf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "sqrtf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "erf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "erff", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "erfc", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "erfcf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "lgamma", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "lgammaf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "name": "signgam", 
        "type": "variable"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "tgamma", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "tgammaf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "ceilf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "floorf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "nearbyint", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "nearbyintf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "rint", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "rintf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "lrint", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "lrintf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "round", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "roundf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "lround", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "lroundf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "trunc", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "truncf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "fmodf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "remainder", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "remainderf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "", 
                "qualifiers": []
            }
        ], 
        "name": "remquo", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "", 
                "qualifiers": []
            }
        ], 
        "name": "remquof", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "copysign", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "copysignf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "tagp", 
                "name": "String"
            }
        ], 
        "name": "nan", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "tagp", 
                "name": "String"
            }
        ], 
        "name": "nanf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "nextafter", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "nextafterf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "x", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "y", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "fdim", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "x", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "y", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "fdimf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "fmax", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "fmaxf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "fmin", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "fminf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "fma", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "fmaf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Number", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Sign", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "_copysignf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "_chgsignf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "_logbf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_Y", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "_nextafterf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "float", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "_finitef", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "_isnanf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "_X", 
                "longs": 0, 
                "name": "float", 
                "signed": true
            }
        ], 
        "name": "_fpclassf", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "sd_ver_major", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "uint32_t", 
            "signed": true
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "sd_ver_minor", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "uint32_t", 
            "signed": true
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "ConstantExpressionNode", 
                    "errors": [], 
                    "value": 0
                }, 
                "name": "SD_OK"
            }, 
            {
                "ctype": {
                    "Klass": "BinaryExpressionNode", 
                    "can_be_ctype": [
                        false, 
                        false
                    ], 
                    "errors": [], 
                    "format": "(%s + %s)", 
                    "left": {
                        "Klass": "IdentifierExpressionNode", 
                        "errors": [], 
                        "name": "SD_OK"
                    }, 
                    "name": "addition", 
                    "right": {
                        "Klass": "ConstantExpressionNode", 
                        "errors": [], 
                        "value": 1
                    }
                }, 
                "name": "SD_ERR"
            }, 
            {
                "ctype": {
                    "Klass": "BinaryExpressionNode", 
                    "can_be_ctype": [
                        false, 
                        false
                    ], 
                    "errors": [], 
                    "format": "(%s + %s)", 
                    "left": {
                        "Klass": "IdentifierExpressionNode", 
                        "errors": [], 
                        "name": "SD_ERR"
                    }, 
                    "name": "addition", 
                    "right": {
                        "Klass": "ConstantExpressionNode", 
                        "errors": [], 
                        "value": 1
                    }
                }, 
                "name": "SD_CONT"
            }, 
            {
                "ctype": {
                    "Klass": "BinaryExpressionNode", 
                    "can_be_ctype": [
                        false, 
                        false
                    ], 
                    "errors": [], 
                    "format": "(%s + %s)", 
                    "left": {
                        "Klass": "IdentifierExpressionNode", 
                        "errors": [], 
                        "name": "SD_CONT"
                    }, 
                    "name": "addition", 
                    "right": {
                        "Klass": "ConstantExpressionNode", 
                        "errors": [], 
                        "value": 1
                    }
                }, 
                "name": "SD_STOP"
            }
        ], 
        "name": "sd_stat", 
        "type": "enum"
    }, 
    {
        "name": "SD_OK", 
        "type": "constant", 
        "value": "0"
    }, 
    {
        "name": "SD_ERR", 
        "type": "constant", 
        "value": "(SD_OK + 1)"
    }, 
    {
        "name": "SD_CONT", 
        "type": "constant", 
        "value": "(SD_ERR + 1)"
    }, 
    {
        "name": "SD_STOP", 
        "type": "constant", 
        "value": "(SD_CONT + 1)"
    }, 
    {
        "ctype": {
            "Klass": "CtypesEnum", 
            "anonymous": false, 
            "enumerators": [
                [
                    "SD_OK", 
                    {
                        "Klass": "ConstantExpressionNode", 
                        "errors": [], 
                        "value": 0
                    }
                ], 
                [
                    "SD_ERR", 
                    {
                        "Klass": "BinaryExpressionNode", 
                        "can_be_ctype": [
                            false, 
                            false
                        ], 
                        "errors": [], 
                        "format": "(%s + %s)", 
                        "left": {
                            "Klass": "IdentifierExpressionNode", 
                            "errors": [], 
                            "name": "SD_OK"
                        }, 
                        "name": "addition", 
                        "right": {
                            "Klass": "ConstantExpressionNode", 
                            "errors": [], 
                            "value": 1
                        }
                    }
                ], 
                [
                    "SD_CONT", 
                    {
                        "Klass": "BinaryExpressionNode", 
                        "can_be_ctype": [
                            false, 
                            false
                        ], 
                        "errors": [], 
                        "format": "(%s + %s)", 
                        "left": {
                            "Klass": "IdentifierExpressionNode", 
                            "errors": [], 
                            "name": "SD_ERR"
                        }, 
                        "name": "addition", 
                        "right": {
                            "Klass": "ConstantExpressionNode", 
                            "errors": [], 
                            "value": 1
                        }
                    }
                ], 
                [
                    "SD_STOP", 
                    {
                        "Klass": "BinaryExpressionNode", 
                        "can_be_ctype": [
                            false, 
                            false
                        ], 
                        "errors": [], 
                        "format": "(%s + %s)", 
                        "left": {
                            "Klass": "IdentifierExpressionNode", 
                            "errors": [], 
                            "name": "SD_CONT"
                        }, 
                        "name": "addition", 
                        "right": {
                            "Klass": "ConstantExpressionNode", 
                            "errors": [], 
                            "value": 1
                        }
                    }
                ]
            ], 
            "errors": [], 
            "opaque": false, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                61
            ], 
            "tag": "sd_stat"
        }, 
        "name": "sd_stat", 
        "type": "typedef"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "fname", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "uint32_t", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "n", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "w", 
                "qualifiers": []
            }
        ], 
        "name": "sd_util_read_square_matrix", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "sd_stat"
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "n", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "uint32_t", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "ints", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "uint32_t", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "nuniq", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "uints", 
                "qualifiers": []
            }
        ], 
        "name": "sd_util_uniqi", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "sd_stat"
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "ptr"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_rng"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "seed", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "seed"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_rng"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "norm"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_rng"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "n", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "identifier": "x", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "fill_norm"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_rng"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "nbytes"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_rng"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "free"
            }
        ], 
        "name": "sd_rng", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": null, 
            "opaque": true, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                105
            ], 
            "tag": "sd_rng", 
            "variety": "struct"
        }, 
        "name": "sd_rng", 
        "type": "typedef"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "sd_rng"
                }, 
                "errors": [], 
                "identifier": "", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "seed", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }
        ], 
        "name": "sd_rng_seed", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "sd_rng"
                }, 
                "errors": [], 
                "identifier": "", 
                "qualifiers": []
            }
        ], 
        "name": "sd_rng_norm", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "sd_rng"
                }, 
                "errors": [], 
                "identifier": "", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "n", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "x", 
                "qualifiers": []
            }
        ], 
        "name": "sd_rng_fill_norm", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "sd_rng"
                }, 
                "errors": [], 
                "identifier": "", 
                "qualifiers": []
            }
        ], 
        "name": "sd_rng_nbytes", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "uint32_t", 
            "signed": true
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "sd_rng"
                }, 
                "errors": [], 
                "identifier": "", 
                "qualifiers": []
            }
        ], 
        "name": "sd_rng_free", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "sd_rng_new_default", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_rng"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "ptr"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hfill"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "n", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "identifier": "t", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "identifier": "indices", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "identifier": "buf", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "sd_stat"
                    }, 
                    "variadic": false
                }, 
                "name": "apply"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hfill"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "free"
            }
        ], 
        "name": "sd_hfill", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": null, 
            "opaque": true, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                154
            ], 
            "tag": "sd_hfill", 
            "variety": "struct"
        }, 
        "name": "sd_hfill", 
        "type": "typedef"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "sd_hfill"
                }, 
                "errors": [], 
                "identifier": "", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "n", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "t", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "uint32_t", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "indices", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "buf", 
                "qualifiers": []
            }
        ], 
        "name": "sd_hfill_apply", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "sd_stat"
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "sd_hfill"
                }, 
                "errors": [], 
                "identifier": "", 
                "qualifiers": []
            }
        ], 
        "name": "sd_hfill_free", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "val", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "sd_hfill_new_val", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_hfill"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "ptr"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_maxvi"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "vi", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_vi2i"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "h", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_nu"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "h", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "free"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "h", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hfill"
                            }, 
                            "errors": [], 
                            "identifier": "filler", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "sd_stat"
                    }, 
                    "variadic": false
                }, 
                "name": "fill"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "h", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "t", 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "identifier": "aff", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "h", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "t", 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "identifier": "eff", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "set"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "h", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "nbytes"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "h", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "index", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_buf_lin"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "h", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_nd"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "h", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_t"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "h", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_dt"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "h", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "i", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_lim"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "h", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "i", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_len"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "h", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "i", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_pos"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "h", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "i", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_uvi"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "h", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "i", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_maxd"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "h", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "i", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_vi"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "h", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "i", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_vd"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "h", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "_Bool", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "buf_is_null"
            }
        ], 
        "name": "sd_hist", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": null, 
            "opaque": true, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                195
            ], 
            "tag": "sd_hist", 
            "variety": "struct"
        }, 
        "name": "sd_hist", 
        "type": "typedef"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "nd", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "uint32_t", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "vi", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "vd", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "t0", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "dt", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "sd_hist_new_default", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_hist"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "ctype": {
            "Klass": "CtypesFunction", 
            "argtypes": [
                {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "identifier": "ptr", 
                    "qualifiers": []
                }
            ], 
            "errors": [], 
            "restype": {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "longs": 0, 
                "name": "void", 
                "signed": true
            }, 
            "variadic": false
        }, 
        "name": "sd_free_t", 
        "type": "typedef"
    }, 
    {
        "args": [], 
        "name": "sd_malloc_set_stdlib_allocators", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "void", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "ptr", 
                "qualifiers": []
            }
        ], 
        "name": "sd_free", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "uint32_t", 
                    "signed": true
                }, 
                "name": "nx"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "uint32_t", 
                    "signed": true
                }, 
                "name": "nc"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "uint32_t", 
                    "signed": true
                }, 
                "name": "id"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "name": "t"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "x"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "i"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "sd_hist"
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "hist"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "sd_rng"
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "rng"
            }
        ], 
        "name": "sd_sys_in", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "nx", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }
                ], 
                [
                    "nc", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }
                ], 
                [
                    "id", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }
                ], 
                [
                    "t", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }
                ], 
                [
                    "x", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "i", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "hist", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_hist"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "rng", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_rng"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                453
            ], 
            "tag": "sd_sys_in", 
            "variety": "struct"
        }, 
        "name": "sd_sys_in", 
        "type": "typedef"
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "f"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "g"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "o"
            }
        ], 
        "name": "sd_sys_out", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "f", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "g", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "o", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                460
            ], 
            "tag": "sd_sys_out", 
            "variety": "struct"
        }, 
        "name": "sd_sys_out", 
        "type": "typedef"
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "ndim"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "ndc"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "nobs"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "nrpar"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "nipar"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys_in"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys_out"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "sd_stat"
                    }, 
                    "variadic": false
                }, 
                "name": "apply"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "free"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "ptr"
            }
        ], 
        "name": "sd_sys", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": null, 
            "opaque": true, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                465
            ], 
            "tag": "sd_sys", 
            "variety": "struct"
        }, 
        "name": "sd_sys", 
        "type": "typedef"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "ndim", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "ndc", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "nobs", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "nrpar", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "nipar", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "void", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "user_data", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesFunction", 
                "argtypes": [
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "identifier": "", 
                        "qualifiers": []
                    }, 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_sys_in"
                        }, 
                        "errors": [], 
                        "identifier": "", 
                        "qualifiers": []
                    }, 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_sys_out"
                        }, 
                        "errors": [], 
                        "identifier": "", 
                        "qualifiers": []
                    }
                ], 
                "errors": [], 
                "restype": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "sd_stat"
                }, 
                "variadic": false
            }
        ], 
        "name": "sd_sys_new_cb", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_sys"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "ptr"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys_exc"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_sys"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "sys"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys_exc"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_a"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys_exc"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "new_a", 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "set_a"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys_exc"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_tau"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys_exc"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "new_tau", 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "set_tau"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys_exc"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_D"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys_exc"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "new_D", 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "set_D"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys_exc"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_k"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys_exc"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "new_k", 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "set_k"
            }
        ], 
        "name": "sd_sys_exc", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": null, 
            "opaque": true, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                528
            ], 
            "tag": "sd_sys_exc", 
            "variety": "struct"
        }, 
        "name": "sd_sys_exc", 
        "type": "typedef"
    }, 
    {
        "args": [], 
        "name": "sd_sys_exc_new", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_sys_exc"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "ptr"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_sys"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "sys"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "free"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "net", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_n"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "net", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_m"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "net", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_nnz"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "net", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_or"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "net", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "i", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_or_i"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "net", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_ic"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "net", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "i", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_ic_i"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "net", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_w"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "net", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "i", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_w_i"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "net", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_d"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "net", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "i", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_d_i"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "net", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_ns"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "net", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_ne"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "net", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "_Bool", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "cn_is_null"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "net", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "i", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_Ms_i"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "net", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "i", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_Ma_i"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "net", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "i", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_Me_i"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "net", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "i", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_M_i"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "net", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "i", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_sys"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_models_i"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_net"
                            }, 
                            "errors": [], 
                            "identifier": "net", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "_Bool", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get__init1"
            }
        ], 
        "name": "sd_net", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": null, 
            "opaque": true, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                644
            ], 
            "tag": "sd_net", 
            "variety": "struct"
        }, 
        "name": "sd_net", 
        "type": "typedef"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "n", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "m", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "uint32_t", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "M", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "uint32_t", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "Ms", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "uint32_t", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "Ma", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "uint32_t", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "Me", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "sd_sys"
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "models", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "nnz", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "uint32_t", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "Or", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "uint32_t", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "Ic", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "w", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "d", 
                "qualifiers": []
            }
        ], 
        "name": "sd_net_new_het", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_net"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "n", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "sd_sys"
                }, 
                "errors": [], 
                "identifier": "sys", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "ns", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "na", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "ne", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "nnz", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "uint32_t", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "Or", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "uint32_t", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "Ic", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "w", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "d", 
                "qualifiers": []
            }
        ], 
        "name": "sd_net_new_hom", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_net"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "n", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "uint32_t", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "map", 
                "qualifiers": []
            }
        ], 
        "name": "sd_roi_new_default", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_sys"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "ptr"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "free"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "t", 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "nx", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "identifier": "x", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "nc", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "identifier": "c", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "sd_stat"
                    }, 
                    "variadic": false
                }, 
                "name": "apply"
            }
        ], 
        "name": "sd_out", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": null, 
            "opaque": true, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                867
            ], 
            "tag": "sd_out", 
            "variety": "struct"
        }, 
        "name": "sd_out", 
        "type": "typedef"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "void", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "user_data", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesFunction", 
                "argtypes": [
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "identifier": "", 
                        "qualifiers": []
                    }, 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "identifier": "t", 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "identifier": "nx", 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "identifier": "x", 
                        "qualifiers": []
                    }, 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "identifier": "nc", 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "identifier": "c", 
                        "qualifiers": []
                    }
                ], 
                "errors": [], 
                "restype": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "sd_stat"
                }, 
                "variadic": false
            }
        ], 
        "name": "sd_out_new_cb", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_out"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "ptr"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_file"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_out"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "out"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_file"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "_Bool", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "is_std"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_file"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "FILE"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_fd"
            }
        ], 
        "name": "sd_out_file", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": null, 
            "opaque": true, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                908
            ], 
            "tag": "sd_out_file", 
            "variety": "struct"
        }, 
        "name": "sd_out_file", 
        "type": "typedef"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "fname", 
                "name": "String"
            }
        ], 
        "name": "sd_out_file_new_from_name", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_out_file"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "FILE"
                }, 
                "errors": [], 
                "identifier": "std", 
                "qualifiers": []
            }
        ], 
        "name": "sd_out_file_new_from_std", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_out_file"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "ptr"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_mem"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_out"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "out"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_mem"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_nx"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_mem"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_nc"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_mem"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_n_sample"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_mem"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_capacity"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_mem"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_xs"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_mem"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_cs"
            }
        ], 
        "name": "sd_out_mem", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": null, 
            "opaque": true, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                959
            ], 
            "tag": "sd_out_mem", 
            "variety": "struct"
        }, 
        "name": "sd_out_mem", 
        "type": "typedef"
    }, 
    {
        "args": [], 
        "name": "sd_out_mem_new", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_out_mem"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "ptr"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_tee"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_out"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "out"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_tee"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_nout"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_tee"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "_Bool", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "outs_is_null"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_tee"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "i", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out"
                            }, 
                            "errors": [], 
                            "identifier": "out", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "sd_stat"
                    }, 
                    "variadic": false
                }, 
                "name": "set_out"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_tee"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "i", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_out"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_out"
            }
        ], 
        "name": "sd_out_tee", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": null, 
            "opaque": true, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                1030
            ], 
            "tag": "sd_out_tee", 
            "variety": "struct"
        }, 
        "name": "sd_out_tee", 
        "type": "typedef"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "nout", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }
        ], 
        "name": "sd_out_tee_new", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_out_tee"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "ptr"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_tavg"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_out"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "out"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_tavg"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_len"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_tavg"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_pos"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_tavg"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_t"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_tavg"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_out"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_out"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_tavg"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_x"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_tavg"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_c"
            }
        ], 
        "name": "sd_out_tavg", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": null, 
            "opaque": true, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                1094
            ], 
            "tag": "sd_out_tavg", 
            "variety": "struct"
        }, 
        "name": "sd_out_tavg", 
        "type": "typedef"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "len", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "sd_out"
                }, 
                "errors": [], 
                "identifier": "out", 
                "qualifiers": []
            }
        ], 
        "name": "sd_out_tavg_new", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_out_tavg"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "ptr"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_sfilt"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_out"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "out"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_sfilt"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_nfilt"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_sfilt"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_filtlen"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_sfilt"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_xfilts"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_sfilt"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_cfilts"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_sfilt"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_x"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_sfilt"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_c"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out_sfilt"
                            }, 
                            "errors": [], 
                            "identifier": "d", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_out"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_out"
            }
        ], 
        "name": "sd_out_sfilt", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": null, 
            "opaque": true, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                1147
            ], 
            "tag": "sd_out_sfilt", 
            "variety": "struct"
        }, 
        "name": "sd_out_sfilt", 
        "type": "typedef"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "nfilt", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "filtlen", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "xfilts", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "cfilts", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "sd_out"
                }, 
                "errors": [], 
                "identifier": "out", 
                "qualifiers": []
            }
        ], 
        "name": "sd_out_sfilt_new", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_out_sfilt"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "time", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "sd_out_new_until", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_out"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "ignore_x", 
                "longs": 0, 
                "name": "_Bool", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "ignore_c", 
                "longs": 0, 
                "name": "_Bool", 
                "signed": true
            }
        ], 
        "name": "sd_out_ignore", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_out"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "ptr"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sch"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_nx"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sch"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_rng"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "t", 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "dt", 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "nx", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "identifier": "x", 
                            "qualifiers": []
                        }, 
                        {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "identifier": "nc", 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "identifier": "c", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "sd_stat"
                    }, 
                    "variadic": false
                }, 
                "name": "apply"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sch"
                            }, 
                            "errors": [], 
                            "identifier": "", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "free"
            }
        ], 
        "name": "sd_sch", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": null, 
            "opaque": true, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                1229
            ], 
            "tag": "sd_sch", 
            "variety": "struct"
        }, 
        "name": "sd_sch", 
        "type": "typedef"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "nx", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "void", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "user_data", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesFunction", 
                "argtypes": [
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "identifier": "", 
                        "qualifiers": []
                    }, 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_hist"
                        }, 
                        "errors": [], 
                        "identifier": "", 
                        "qualifiers": []
                    }, 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_rng"
                        }, 
                        "errors": [], 
                        "identifier": "", 
                        "qualifiers": []
                    }, 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_sys"
                        }, 
                        "errors": [], 
                        "identifier": "", 
                        "qualifiers": []
                    }, 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "identifier": "t", 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "identifier": "dt", 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "identifier": "nx", 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "identifier": "x", 
                        "qualifiers": []
                    }, 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "identifier": "nc", 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "identifier": "c", 
                        "qualifiers": []
                    }
                ], 
                "errors": [], 
                "restype": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "sd_stat"
                }, 
                "variadic": false
            }
        ], 
        "name": "sd_sch_new_cb", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_sch"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "nx", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }
        ], 
        "name": "sd_sch_new_id", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_sch"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "nx", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }
        ], 
        "name": "sd_sch_new_em", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_sch"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "nx", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "lam", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "sd_sch_new_emc", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_sch"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "sd_sch"
                }, 
                "errors": [], 
                "identifier": "sch", 
                "qualifiers": []
            }
        ], 
        "name": "sd_sch_emcolor_get_lam", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "double", 
            "signed": true
        }, 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "nx", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }
        ], 
        "name": "sd_sch_new_heun", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_sch"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "fields": [
            {
                "ctype": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "name": "ptr"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sol"
                            }, 
                            "errors": [], 
                            "identifier": "s", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "void", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "free"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sol"
                            }, 
                            "errors": [], 
                            "identifier": "s", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "sd_stat"
                    }, 
                    "variadic": false
                }, 
                "name": "cont"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sol"
                            }, 
                            "errors": [], 
                            "identifier": "s", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_nx"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sol"
                            }, 
                            "errors": [], 
                            "identifier": "s", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_nce"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sol"
                            }, 
                            "errors": [], 
                            "identifier": "s", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_nca"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sol"
                            }, 
                            "errors": [], 
                            "identifier": "s", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_hist"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_hist"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sol"
                            }, 
                            "errors": [], 
                            "identifier": "s", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_rng"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_rng"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sol"
                            }, 
                            "errors": [], 
                            "identifier": "s", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "variadic": false
                }, 
                "name": "get_t"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sol"
                            }, 
                            "errors": [], 
                            "identifier": "s", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_x"
            }, 
            {
                "ctype": {
                    "Klass": "CtypesFunction", 
                    "argtypes": [
                        {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sol"
                            }, 
                            "errors": [], 
                            "identifier": "s", 
                            "qualifiers": []
                        }
                    ], 
                    "errors": [], 
                    "restype": {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }, 
                    "variadic": false
                }, 
                "name": "get_c"
            }
        ], 
        "name": "sd_sol", 
        "type": "struct"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": null, 
            "opaque": true, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                1344
            ], 
            "tag": "sd_sol", 
            "variety": "struct"
        }, 
        "name": "sd_sol", 
        "type": "typedef"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "sd_sys"
                }, 
                "errors": [], 
                "identifier": "sys", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "sd_sch"
                }, 
                "errors": [], 
                "identifier": "scheme", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "sd_out"
                }, 
                "errors": [], 
                "identifier": "out", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesTypedef", 
                    "errors": [], 
                    "name": "sd_hfill"
                }, 
                "errors": [], 
                "identifier": "hf", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "seed", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "nx", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "x0", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "nce", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "nca", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "uint32_t", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "vi", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "vd", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "t0", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "dt", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }
        ], 
        "name": "sd_sol_new_default", 
        "return": {
            "Klass": "CtypesPointer", 
            "destination": {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "name": "sd_sol"
            }, 
            "errors": [], 
            "qualifiers": []
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "m", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "n", 
                "longs": 0, 
                "name": "uint32_t", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "dA", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "double", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "dB", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "eps", 
                "longs": 0, 
                "name": "double", 
                "signed": true
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "longs": 0, 
                    "name": "uint32_t", 
                    "signed": true
                }, 
                "errors": [], 
                "identifier": "nnz", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "Or", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "Ic", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "sA", 
                "qualifiers": []
            }, 
            {
                "Klass": "CtypesPointer", 
                "destination": {
                    "Klass": "CtypesPointer", 
                    "destination": {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }, 
                    "errors": [], 
                    "qualifiers": []
                }, 
                "errors": [], 
                "identifier": "sB", 
                "qualifiers": []
            }
        ], 
        "name": "sd_sparse_from_dense", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "sd_stat"
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "ctype": {
            "Klass": "CtypesFunction", 
            "argtypes": [
                {
                    "Klass": "CtypesSpecial", 
                    "errors": [], 
                    "identifier": "fmt", 
                    "name": "String"
                }
            ], 
            "errors": [], 
            "restype": {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            "variadic": true
        }, 
        "name": "sd_log_msg_fp", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "sd_log_msg_fp"
        }, 
        "name": "sd_log_msg", 
        "source": "SDDEKit", 
        "type": "variable"
    }, 
    {
        "args": [], 
        "name": "sd_log_get_msg", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "sd_log_msg_fp"
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "fp", 
                "name": "sd_log_msg_fp"
            }
        ], 
        "name": "sd_log_set_msg", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "sd_log_is_quiet", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "_Bool", 
            "signed": true
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "flag", 
                "longs": 0, 
                "name": "_Bool", 
                "signed": true
            }
        ], 
        "name": "sd_log_set_quiet", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "sd_log_is_verbose", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "_Bool", 
            "signed": true
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "flag", 
                "longs": 0, 
                "name": "_Bool", 
                "signed": true
            }
        ], 
        "name": "sd_log_set_verbose", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "ctype": {
            "Klass": "CtypesFunction", 
            "argtypes": [
                {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "identifier": "err", 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                {
                    "Klass": "CtypesSpecial", 
                    "errors": [], 
                    "identifier": "file", 
                    "name": "String"
                }, 
                {
                    "Klass": "CtypesSimple", 
                    "errors": [], 
                    "identifier": "line", 
                    "longs": 0, 
                    "name": "int", 
                    "signed": true
                }, 
                {
                    "Klass": "CtypesSpecial", 
                    "errors": [], 
                    "identifier": "func", 
                    "name": "String"
                }, 
                {
                    "Klass": "CtypesSpecial", 
                    "errors": [], 
                    "identifier": "reason", 
                    "name": "String"
                }
            ], 
            "errors": [], 
            "restype": {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "longs": 0, 
                "name": "void", 
                "signed": true
            }, 
            "variadic": false
        }, 
        "name": "sd_err_handler_fp", 
        "type": "typedef"
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "err", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "file", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "line", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "func", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "reason", 
                "name": "String"
            }
        ], 
        "name": "sd_err_default_handler", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [], 
        "name": "sd_err_get_handler", 
        "return": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "sd_err_handler_fp"
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesTypedef", 
                "errors": [], 
                "identifier": "fp", 
                "name": "sd_err_handler_fp"
            }
        ], 
        "name": "sd_err_set_handler", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "args": [
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "err", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "file", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSimple", 
                "errors": [], 
                "identifier": "line", 
                "longs": 0, 
                "name": "int", 
                "signed": true
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "func", 
                "name": "String"
            }, 
            {
                "Klass": "CtypesSpecial", 
                "errors": [], 
                "identifier": "reason", 
                "name": "String"
            }
        ], 
        "name": "sd_err_handler", 
        "return": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "void", 
            "signed": true
        }, 
        "source": "SDDEKit", 
        "type": "function", 
        "variadic": false
    }, 
    {
        "name": "__STDC__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__STDC_VERSION__", 
        "type": "macro", 
        "value": "201112L"
    }, 
    {
        "name": "__STDC_UTF_16__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__STDC_UTF_32__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__STDC_HOSTED__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__GNUC__", 
        "type": "macro", 
        "value": "5"
    }, 
    {
        "name": "__GNUC_MINOR__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__GNUC_PATCHLEVEL__", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "__VERSION__", 
        "type": "macro", 
        "value": "'5.1.0'"
    }, 
    {
        "name": "__ATOMIC_RELAXED", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "__ATOMIC_SEQ_CST", 
        "type": "macro", 
        "value": "5"
    }, 
    {
        "name": "__ATOMIC_ACQUIRE", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "__ATOMIC_RELEASE", 
        "type": "macro", 
        "value": "3"
    }, 
    {
        "name": "__ATOMIC_ACQ_REL", 
        "type": "macro", 
        "value": "4"
    }, 
    {
        "name": "__ATOMIC_CONSUME", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__pic__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__PIC__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__FINITE_MATH_ONLY__", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "__SIZEOF_INT__", 
        "type": "macro", 
        "value": "4"
    }, 
    {
        "name": "__SIZEOF_LONG__", 
        "type": "macro", 
        "value": "4"
    }, 
    {
        "name": "__SIZEOF_LONG_LONG__", 
        "type": "macro", 
        "value": "8"
    }, 
    {
        "name": "__SIZEOF_SHORT__", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "__SIZEOF_FLOAT__", 
        "type": "macro", 
        "value": "4"
    }, 
    {
        "name": "__SIZEOF_DOUBLE__", 
        "type": "macro", 
        "value": "8"
    }, 
    {
        "name": "__SIZEOF_LONG_DOUBLE__", 
        "type": "macro", 
        "value": "16"
    }, 
    {
        "name": "__SIZEOF_SIZE_T__", 
        "type": "macro", 
        "value": "8"
    }, 
    {
        "name": "__CHAR_BIT__", 
        "type": "macro", 
        "value": "8"
    }, 
    {
        "name": "__BIGGEST_ALIGNMENT__", 
        "type": "macro", 
        "value": "16"
    }, 
    {
        "name": "__ORDER_LITTLE_ENDIAN__", 
        "type": "macro", 
        "value": "1234"
    }, 
    {
        "name": "__ORDER_BIG_ENDIAN__", 
        "type": "macro", 
        "value": "4321"
    }, 
    {
        "name": "__ORDER_PDP_ENDIAN__", 
        "type": "macro", 
        "value": "3412"
    }, 
    {
        "name": "__BYTE_ORDER__", 
        "type": "macro", 
        "value": "__ORDER_LITTLE_ENDIAN__"
    }, 
    {
        "name": "__FLOAT_WORD_ORDER__", 
        "type": "macro", 
        "value": "__ORDER_LITTLE_ENDIAN__"
    }, 
    {
        "name": "__SIZEOF_POINTER__", 
        "type": "macro", 
        "value": "8"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": false
        }, 
        "name": "__WCHAR_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": false
        }, 
        "name": "__WINT_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": false
        }, 
        "name": "__CHAR16_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": false
        }, 
        "name": "__CHAR32_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "name": "__SIG_ATOMIC_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "char", 
            "signed": true
        }, 
        "name": "__INT8_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "name": "__INT16_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "name": "__INT32_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "char", 
            "signed": false
        }, 
        "name": "__UINT8_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": false
        }, 
        "name": "__UINT16_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": false
        }, 
        "name": "__UINT32_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "char", 
            "signed": true
        }, 
        "name": "__INT_LEAST8_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "name": "__INT_LEAST16_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "name": "__INT_LEAST32_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "char", 
            "signed": false
        }, 
        "name": "__UINT_LEAST8_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": false
        }, 
        "name": "__UINT_LEAST16_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": false
        }, 
        "name": "__UINT_LEAST32_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "char", 
            "signed": true
        }, 
        "name": "__INT_FAST8_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "name": "__INT_FAST16_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "name": "__INT_FAST32_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "char", 
            "signed": false
        }, 
        "name": "__UINT_FAST8_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": false
        }, 
        "name": "__UINT_FAST16_TYPE__", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": false
        }, 
        "name": "__UINT_FAST32_TYPE__", 
        "type": "typedef"
    }, 
    {
        "name": "__GXX_ABI_VERSION", 
        "type": "macro", 
        "value": "1008"
    }, 
    {
        "name": "__SCHAR_MAX__", 
        "type": "macro", 
        "value": "127"
    }, 
    {
        "name": "__SHRT_MAX__", 
        "type": "macro", 
        "value": "32767"
    }, 
    {
        "name": "__INT_MAX__", 
        "type": "macro", 
        "value": "2147483647"
    }, 
    {
        "name": "__LONG_MAX__", 
        "type": "macro", 
        "value": "2147483647L"
    }, 
    {
        "name": "__LONG_LONG_MAX__", 
        "type": "macro", 
        "value": "9223372036854775807L"
    }, 
    {
        "name": "__WCHAR_MAX__", 
        "type": "macro", 
        "value": "65535"
    }, 
    {
        "name": "__WCHAR_MIN__", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "__WINT_MAX__", 
        "type": "macro", 
        "value": "65535"
    }, 
    {
        "name": "__WINT_MIN__", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "__PTRDIFF_MAX__", 
        "type": "macro", 
        "value": "9223372036854775807L"
    }, 
    {
        "name": "__SIZE_MAX__", 
        "type": "macro", 
        "value": "18446744073709551615L"
    }, 
    {
        "name": "__INTMAX_MAX__", 
        "type": "macro", 
        "value": "9223372036854775807L"
    }, 
    {
        "name": "__UINTMAX_MAX__", 
        "type": "macro", 
        "value": "18446744073709551615L"
    }, 
    {
        "name": "__SIG_ATOMIC_MAX__", 
        "type": "macro", 
        "value": "2147483647"
    }, 
    {
        "name": "__SIG_ATOMIC_MIN__", 
        "type": "macro", 
        "value": "((-__SIG_ATOMIC_MAX__) - 1)"
    }, 
    {
        "name": "__INT8_MAX__", 
        "type": "macro", 
        "value": "127"
    }, 
    {
        "name": "__INT16_MAX__", 
        "type": "macro", 
        "value": "32767"
    }, 
    {
        "name": "__INT32_MAX__", 
        "type": "macro", 
        "value": "2147483647"
    }, 
    {
        "name": "__INT64_MAX__", 
        "type": "macro", 
        "value": "9223372036854775807L"
    }, 
    {
        "name": "__UINT8_MAX__", 
        "type": "macro", 
        "value": "255"
    }, 
    {
        "name": "__UINT16_MAX__", 
        "type": "macro", 
        "value": "65535"
    }, 
    {
        "name": "__UINT32_MAX__", 
        "type": "macro", 
        "value": "4294967295L"
    }, 
    {
        "name": "__UINT64_MAX__", 
        "type": "macro", 
        "value": "18446744073709551615L"
    }, 
    {
        "name": "__INT_LEAST8_MAX__", 
        "type": "macro", 
        "value": "127"
    }, 
    {
        "args": [
            "c"
        ], 
        "body": "c", 
        "name": "__INT8_C", 
        "type": "macro_function"
    }, 
    {
        "name": "__INT_LEAST16_MAX__", 
        "type": "macro", 
        "value": "32767"
    }, 
    {
        "args": [
            "c"
        ], 
        "body": "c", 
        "name": "__INT16_C", 
        "type": "macro_function"
    }, 
    {
        "name": "__INT_LEAST32_MAX__", 
        "type": "macro", 
        "value": "2147483647"
    }, 
    {
        "args": [
            "c"
        ], 
        "body": "c", 
        "name": "__INT32_C", 
        "type": "macro_function"
    }, 
    {
        "name": "__INT_LEAST64_MAX__", 
        "type": "macro", 
        "value": "9223372036854775807L"
    }, 
    {
        "name": "__UINT_LEAST8_MAX__", 
        "type": "macro", 
        "value": "255"
    }, 
    {
        "args": [
            "c"
        ], 
        "body": "c", 
        "name": "__UINT8_C", 
        "type": "macro_function"
    }, 
    {
        "name": "__UINT_LEAST16_MAX__", 
        "type": "macro", 
        "value": "65535"
    }, 
    {
        "args": [
            "c"
        ], 
        "body": "c", 
        "name": "__UINT16_C", 
        "type": "macro_function"
    }, 
    {
        "name": "__UINT_LEAST32_MAX__", 
        "type": "macro", 
        "value": "4294967295L"
    }, 
    {
        "name": "__UINT_LEAST64_MAX__", 
        "type": "macro", 
        "value": "18446744073709551615L"
    }, 
    {
        "name": "__INT_FAST8_MAX__", 
        "type": "macro", 
        "value": "127"
    }, 
    {
        "name": "__INT_FAST16_MAX__", 
        "type": "macro", 
        "value": "32767"
    }, 
    {
        "name": "__INT_FAST32_MAX__", 
        "type": "macro", 
        "value": "2147483647"
    }, 
    {
        "name": "__INT_FAST64_MAX__", 
        "type": "macro", 
        "value": "9223372036854775807L"
    }, 
    {
        "name": "__UINT_FAST8_MAX__", 
        "type": "macro", 
        "value": "255"
    }, 
    {
        "name": "__UINT_FAST16_MAX__", 
        "type": "macro", 
        "value": "65535"
    }, 
    {
        "name": "__UINT_FAST32_MAX__", 
        "type": "macro", 
        "value": "4294967295L"
    }, 
    {
        "name": "__UINT_FAST64_MAX__", 
        "type": "macro", 
        "value": "18446744073709551615L"
    }, 
    {
        "name": "__INTPTR_MAX__", 
        "type": "macro", 
        "value": "9223372036854775807L"
    }, 
    {
        "name": "__UINTPTR_MAX__", 
        "type": "macro", 
        "value": "18446744073709551615L"
    }, 
    {
        "name": "__GCC_IEC_559", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "__GCC_IEC_559_COMPLEX", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "__FLT_EVAL_METHOD__", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "__DEC_EVAL_METHOD__", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "__FLT_RADIX__", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "__FLT_MANT_DIG__", 
        "type": "macro", 
        "value": "24"
    }, 
    {
        "name": "__FLT_DIG__", 
        "type": "macro", 
        "value": "6"
    }, 
    {
        "name": "__FLT_MIN_EXP__", 
        "type": "macro", 
        "value": "(-125)"
    }, 
    {
        "name": "__FLT_MIN_10_EXP__", 
        "type": "macro", 
        "value": "(-37)"
    }, 
    {
        "name": "__FLT_MAX_EXP__", 
        "type": "macro", 
        "value": "128"
    }, 
    {
        "name": "__FLT_MAX_10_EXP__", 
        "type": "macro", 
        "value": "38"
    }, 
    {
        "name": "__FLT_DECIMAL_DIG__", 
        "type": "macro", 
        "value": "9"
    }, 
    {
        "name": "__FLT_MAX__", 
        "type": "macro", 
        "value": "3.4028234663852886e+38"
    }, 
    {
        "name": "__FLT_MIN__", 
        "type": "macro", 
        "value": "1.1754943508222875e-38"
    }, 
    {
        "name": "__FLT_EPSILON__", 
        "type": "macro", 
        "value": "1.1920928955078125e-07"
    }, 
    {
        "name": "__FLT_DENORM_MIN__", 
        "type": "macro", 
        "value": "1.401298464324817e-45"
    }, 
    {
        "name": "__FLT_HAS_DENORM__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__FLT_HAS_INFINITY__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__FLT_HAS_QUIET_NAN__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__DBL_MANT_DIG__", 
        "type": "macro", 
        "value": "53"
    }, 
    {
        "name": "__DBL_DIG__", 
        "type": "macro", 
        "value": "15"
    }, 
    {
        "name": "__DBL_MIN_EXP__", 
        "type": "macro", 
        "value": "(-1021)"
    }, 
    {
        "name": "__DBL_MIN_10_EXP__", 
        "type": "macro", 
        "value": "(-307)"
    }, 
    {
        "name": "__DBL_MAX_EXP__", 
        "type": "macro", 
        "value": "1024"
    }, 
    {
        "name": "__DBL_MAX_10_EXP__", 
        "type": "macro", 
        "value": "308"
    }, 
    {
        "name": "__DBL_DECIMAL_DIG__", 
        "type": "macro", 
        "value": "17"
    }, 
    {
        "name": "__DBL_MAX__", 
        "type": "macro", 
        "value": "1.7976931348623157e+308"
    }, 
    {
        "name": "__DBL_MIN__", 
        "type": "macro", 
        "value": "2.2250738585072014e-308"
    }, 
    {
        "name": "__DBL_EPSILON__", 
        "type": "macro", 
        "value": "2.220446049250313e-16"
    }, 
    {
        "name": "__DBL_DENORM_MIN__", 
        "type": "macro", 
        "value": "5e-324"
    }, 
    {
        "name": "__DBL_HAS_DENORM__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__DBL_HAS_INFINITY__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__DBL_HAS_QUIET_NAN__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__LDBL_MANT_DIG__", 
        "type": "macro", 
        "value": "64"
    }, 
    {
        "name": "__LDBL_DIG__", 
        "type": "macro", 
        "value": "18"
    }, 
    {
        "name": "__LDBL_MIN_EXP__", 
        "type": "macro", 
        "value": "(-16381)"
    }, 
    {
        "name": "__LDBL_MIN_10_EXP__", 
        "type": "macro", 
        "value": "(-4931)"
    }, 
    {
        "name": "__LDBL_MAX_EXP__", 
        "type": "macro", 
        "value": "16384"
    }, 
    {
        "name": "__LDBL_MAX_10_EXP__", 
        "type": "macro", 
        "value": "4932"
    }, 
    {
        "name": "__DECIMAL_DIG__", 
        "type": "macro", 
        "value": "21"
    }, 
    {
        "name": "__LDBL_MAX__", 
        "type": "macro", 
        "value": "float('inf')"
    }, 
    {
        "name": "__LDBL_MIN__", 
        "type": "macro", 
        "value": "0.0"
    }, 
    {
        "name": "__LDBL_EPSILON__", 
        "type": "macro", 
        "value": "1.0842021724855044e-19"
    }, 
    {
        "name": "__LDBL_DENORM_MIN__", 
        "type": "macro", 
        "value": "0.0"
    }, 
    {
        "name": "__LDBL_HAS_DENORM__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__LDBL_HAS_INFINITY__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__LDBL_HAS_QUIET_NAN__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__DEC32_MANT_DIG__", 
        "type": "macro", 
        "value": "7"
    }, 
    {
        "name": "__DEC32_MIN_EXP__", 
        "type": "macro", 
        "value": "(-94)"
    }, 
    {
        "name": "__DEC32_MAX_EXP__", 
        "type": "macro", 
        "value": "97"
    }, 
    {
        "name": "__DEC64_MANT_DIG__", 
        "type": "macro", 
        "value": "16"
    }, 
    {
        "name": "__DEC64_MIN_EXP__", 
        "type": "macro", 
        "value": "(-382)"
    }, 
    {
        "name": "__DEC64_MAX_EXP__", 
        "type": "macro", 
        "value": "385"
    }, 
    {
        "name": "__DEC128_MANT_DIG__", 
        "type": "macro", 
        "value": "34"
    }, 
    {
        "name": "__DEC128_MIN_EXP__", 
        "type": "macro", 
        "value": "(-6142)"
    }, 
    {
        "name": "__DEC128_MAX_EXP__", 
        "type": "macro", 
        "value": "6145"
    }, 
    {
        "name": "__GNUC_STDC_INLINE__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__NO_INLINE__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__GCC_ATOMIC_BOOL_LOCK_FREE", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "__GCC_ATOMIC_CHAR_LOCK_FREE", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "__GCC_ATOMIC_CHAR16_T_LOCK_FREE", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "__GCC_ATOMIC_CHAR32_T_LOCK_FREE", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "__GCC_ATOMIC_WCHAR_T_LOCK_FREE", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "__GCC_ATOMIC_SHORT_LOCK_FREE", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "__GCC_ATOMIC_INT_LOCK_FREE", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "__GCC_ATOMIC_LONG_LOCK_FREE", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "__GCC_ATOMIC_LLONG_LOCK_FREE", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "__GCC_ATOMIC_TEST_AND_SET_TRUEVAL", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__GCC_ATOMIC_POINTER_LOCK_FREE", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "__PRAGMA_REDEFINE_EXTNAME", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__SIZEOF_INT128__", 
        "type": "macro", 
        "value": "16"
    }, 
    {
        "name": "__SIZEOF_WCHAR_T__", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "__SIZEOF_WINT_T__", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "__SIZEOF_PTRDIFF_T__", 
        "type": "macro", 
        "value": "8"
    }, 
    {
        "name": "__amd64", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__amd64__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__x86_64", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__x86_64__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__SIZEOF_FLOAT80__", 
        "type": "macro", 
        "value": "16"
    }, 
    {
        "name": "__SIZEOF_FLOAT128__", 
        "type": "macro", 
        "value": "16"
    }, 
    {
        "name": "__ATOMIC_HLE_ACQUIRE", 
        "type": "macro", 
        "value": "65536"
    }, 
    {
        "name": "__ATOMIC_HLE_RELEASE", 
        "type": "macro", 
        "value": "131072"
    }, 
    {
        "name": "__k8", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__k8__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__code_model_medium__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__MMX__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__SSE__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__SSE2__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__FXSR__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__SSE_MATH__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__SSE2_MATH__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__SEH__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__GXX_MERGED_TYPEINFO_NAMES", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "__GXX_TYPEINFO_EQUALITY_INLINE", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "__MSVCRT__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__MINGW32__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "_WIN32", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__WIN32", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__WIN32__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "WIN32", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__WINNT", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__WINNT__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "WINNT", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "_INTEGRAL_MAX_BITS", 
        "type": "macro", 
        "value": "64"
    }, 
    {
        "name": "__MINGW64__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__WIN64", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__WIN64__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "WIN64", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "_WIN64", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__DECIMAL_BID_FORMAT__", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "_REENTRANT", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "int", 
            "signed": true
        }, 
        "name": "__const", 
        "type": "typedef"
    }, 
    {
        "name": "CTYPESGEN", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "args": [
            "x"
        ], 
        "body": "x", 
        "name": "__STRINGIFY", 
        "type": "macro_function"
    }, 
    {
        "args": [
            "x"
        ], 
        "body": "(__STRINGIFY (x))", 
        "name": "__MINGW64_STRINGIFY", 
        "type": "macro_function"
    }, 
    {
        "name": "__MINGW64_VERSION_MAJOR", 
        "type": "macro", 
        "value": "4"
    }, 
    {
        "name": "__MINGW64_VERSION_MINOR", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "__MINGW64_VERSION_RC", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "__MINGW64_VERSION_STATE", 
        "type": "macro", 
        "value": "'stable'"
    }, 
    {
        "name": "__MINGW32_MAJOR_VERSION", 
        "type": "macro", 
        "value": "3"
    }, 
    {
        "name": "__MINGW32_MINOR_VERSION", 
        "type": "macro", 
        "value": "11"
    }, 
    {
        "name": "_", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__MINGW_USE_UNDERSCORE_PREFIX", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "args": [
            "sym"
        ], 
        "body": "sym", 
        "name": "__MINGW_USYMBOL", 
        "type": "macro_function"
    }, 
    {
        "name": "_M_AMD64", 
        "type": "macro", 
        "value": "100"
    }, 
    {
        "name": "_M_X64", 
        "type": "macro", 
        "value": "100"
    }, 
    {
        "name": "__MINGW_HAVE_ANSI_C99_PRINTF", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__MINGW_HAVE_WIDE_C99_PRINTF", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__MINGW_HAVE_ANSI_C99_SCANF", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__MINGW_HAVE_WIDE_C99_SCANF", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "__MINGW_GCC_VERSION", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "args": [
            "major", 
            "minor"
        ], 
        "body": "0", 
        "name": "__MINGW_GNUC_PREREQ", 
        "type": "macro_function"
    }, 
    {
        "args": [
            "major", 
            "minor"
        ], 
        "body": "0", 
        "name": "__MINGW_MSC_PREREQ", 
        "type": "macro_function"
    }, 
    {
        "name": "__MINGW_SEC_WARN_STR", 
        "type": "macro", 
        "value": "'This function or variable may be unsafe, use _CRT_SECURE_NO_WARNINGS to disable deprecation'"
    }, 
    {
        "name": "__MINGW_MSVC2005_DEPREC_STR", 
        "type": "macro", 
        "value": "'This POSIX function is deprecated beginning in Visual C++ 2005, use _CRT_NONSTDC_NO_DEPRECATE to disable deprecation'"
    }, 
    {
        "name": "_CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "_CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES_MEMORY", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 1, 
            "name": "int", 
            "signed": true
        }, 
        "name": "__LONG32", 
        "type": "typedef"
    }, 
    {
        "name": "USE___UUIDOF", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "__CRT__NO_INLINE", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "args": [
            "x"
        ], 
        "body": "x", 
        "name": "__UNUSED_PARAM", 
        "type": "macro_function"
    }, 
    {
        "name": "__MSVCRT_VERSION__", 
        "type": "macro", 
        "value": "1792"
    }, 
    {
        "name": "_WIN32_WINNT", 
        "type": "macro", 
        "value": "1282"
    }, 
    {
        "name": "__MINGW_HAS_DXSDK", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "MINGW_HAS_DDRAW_H", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "MINGW_DDRAW_VERSION", 
        "type": "macro", 
        "value": "7"
    }, 
    {
        "name": "MINGW_HAS_DDK_H", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "_CRT_PACKING", 
        "type": "macro", 
        "value": "8"
    }, 
    {
        "args": [
            "v"
        ], 
        "body": "pointer(v)", 
        "name": "_ADDRESSOF", 
        "type": "macro_function"
    }, 
    {
        "args": [
            "_Value"
        ], 
        "body": "_Value", 
        "name": "__CRT_STRINGIZE", 
        "type": "macro_function"
    }, 
    {
        "args": [
            "_Value"
        ], 
        "body": "(__CRT_STRINGIZE (_Value))", 
        "name": "_CRT_STRINGIZE", 
        "type": "macro_function"
    }, 
    {
        "name": "_SECURECRT_FILL_BUFFER_PATTERN", 
        "type": "macro", 
        "value": "253"
    }, 
    {
        "name": "_ARGMAX", 
        "type": "macro", 
        "value": "100"
    }, 
    {
        "args": [
            "x"
        ], 
        "body": "x", 
        "name": "_CRT_UNUSED", 
        "type": "macro_function"
    }, 
    {
        "name": "_CRT_PACKING", 
        "type": "macro", 
        "value": "8"
    }, 
    {
        "name": "BUFSIZ", 
        "type": "macro", 
        "value": "512"
    }, 
    {
        "name": "_NFILE", 
        "type": "macro", 
        "value": "_NSTREAM_"
    }, 
    {
        "name": "_NSTREAM_", 
        "type": "macro", 
        "value": "512"
    }, 
    {
        "name": "_IOB_ENTRIES", 
        "type": "macro", 
        "value": "20"
    }, 
    {
        "name": "EOF", 
        "type": "macro", 
        "value": "(-1)"
    }, 
    {
        "name": "_P_tmpdir", 
        "type": "macro", 
        "value": "'\\\\'"
    }, 
    {
        "name": "L_tmpnam", 
        "type": "macro", 
        "value": "(sizeof(_P_tmpdir) + 12)"
    }, 
    {
        "name": "SEEK_CUR", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "SEEK_END", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "SEEK_SET", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "STDIN_FILENO", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "STDOUT_FILENO", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "STDERR_FILENO", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "FILENAME_MAX", 
        "type": "macro", 
        "value": "260"
    }, 
    {
        "name": "FOPEN_MAX", 
        "type": "macro", 
        "value": "20"
    }, 
    {
        "name": "_SYS_OPEN", 
        "type": "macro", 
        "value": "20"
    }, 
    {
        "name": "TMP_MAX", 
        "type": "macro", 
        "value": "32767"
    }, 
    {
        "name": "_iob", 
        "type": "macro", 
        "value": "(__iob_func ())"
    }, 
    {
        "args": [
            "fp"
        ], 
        "body": "fp", 
        "name": "_FPOSOFF", 
        "type": "macro_function"
    }, 
    {
        "name": "stdin", 
        "type": "macro", 
        "value": "pointer(((__iob_func ()) [0]))"
    }, 
    {
        "name": "stdout", 
        "type": "macro", 
        "value": "pointer(((__iob_func ()) [1]))"
    }, 
    {
        "name": "stderr", 
        "type": "macro", 
        "value": "pointer(((__iob_func ()) [2]))"
    }, 
    {
        "name": "_IOREAD", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "_IOWRT", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "_IOFBF", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "_IOLBF", 
        "type": "macro", 
        "value": "64"
    }, 
    {
        "name": "_IONBF", 
        "type": "macro", 
        "value": "4"
    }, 
    {
        "name": "_IOMYBUF", 
        "type": "macro", 
        "value": "8"
    }, 
    {
        "name": "_IOEOF", 
        "type": "macro", 
        "value": "16"
    }, 
    {
        "name": "_IOERR", 
        "type": "macro", 
        "value": "32"
    }, 
    {
        "name": "_IOSTRG", 
        "type": "macro", 
        "value": "64"
    }, 
    {
        "name": "_IORW", 
        "type": "macro", 
        "value": "128"
    }, 
    {
        "name": "_TWO_DIGIT_EXPONENT", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "popen", 
        "type": "macro", 
        "value": "_popen"
    }, 
    {
        "name": "pclose", 
        "type": "macro", 
        "value": "_pclose"
    }, 
    {
        "name": "WEOF", 
        "type": "macro", 
        "value": "65535"
    }, 
    {
        "name": "wpopen", 
        "type": "macro", 
        "value": "_wpopen"
    }, 
    {
        "name": "getwchar", 
        "type": "macro", 
        "value": "(fgetwc (stdin))"
    }, 
    {
        "args": [
            "_c"
        ], 
        "body": "(fputwc (_c, stdout))", 
        "name": "putwchar", 
        "type": "macro_function"
    }, 
    {
        "args": [
            "_stm"
        ], 
        "body": "(fgetwc (_stm))", 
        "name": "getwc", 
        "type": "macro_function"
    }, 
    {
        "args": [
            "_c", 
            "_stm"
        ], 
        "body": "(fputwc (_c, _stm))", 
        "name": "putwc", 
        "type": "macro_function"
    }, 
    {
        "args": [
            "_c", 
            "_stm"
        ], 
        "body": "(_fputwc_nolock (_c, _stm))", 
        "name": "_putwc_nolock", 
        "type": "macro_function"
    }, 
    {
        "args": [
            "_c"
        ], 
        "body": "(_fgetwc_nolock (_c))", 
        "name": "_getwc_nolock", 
        "type": "macro_function"
    }, 
    {
        "args": [
            "_stream"
        ], 
        "body": "((((_stream.contents._cnt).value) - 1) >= 0) and (255 & ((((_stream.contents._ptr).value) + 1)[0])) or (_filbuf (_stream))", 
        "name": "_fgetc_nolock", 
        "type": "macro_function"
    }, 
    {
        "args": [
            "_c", 
            "_stream"
        ], 
        "body": "((((_stream.contents._cnt).value) - 1) >= 0) and (255 & _c) or (_flsbuf (_c, _stream))", 
        "name": "_fputc_nolock", 
        "type": "macro_function"
    }, 
    {
        "args": [
            "_stream"
        ], 
        "body": "(_fgetc_nolock (_stream))", 
        "name": "_getc_nolock", 
        "type": "macro_function"
    }, 
    {
        "args": [
            "_c", 
            "_stream"
        ], 
        "body": "(_fputc_nolock (_c, _stream))", 
        "name": "_putc_nolock", 
        "type": "macro_function"
    }, 
    {
        "name": "_getchar_nolock", 
        "type": "macro", 
        "value": "(_getc_nolock (stdin))"
    }, 
    {
        "args": [
            "_c"
        ], 
        "body": "(_putc_nolock (_c, stdout))", 
        "name": "_putchar_nolock", 
        "type": "macro_function"
    }, 
    {
        "name": "_getwchar_nolock", 
        "type": "macro", 
        "value": "(_getwc_nolock (stdin))"
    }, 
    {
        "args": [
            "_c"
        ], 
        "body": "(_putwc_nolock (_c, stdout))", 
        "name": "_putwchar_nolock", 
        "type": "macro_function"
    }, 
    {
        "name": "P_tmpdir", 
        "type": "macro", 
        "value": "_P_tmpdir"
    }, 
    {
        "name": "SYS_OPEN", 
        "type": "macro", 
        "value": "_SYS_OPEN"
    }, 
    {
        "name": "_P_WAIT", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "_P_NOWAIT", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "_OLD_P_OVERLAY", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "_P_NOWAITO", 
        "type": "macro", 
        "value": "3"
    }, 
    {
        "name": "_P_DETACH", 
        "type": "macro", 
        "value": "4"
    }, 
    {
        "name": "_P_OVERLAY", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "_WAIT_CHILD", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "_WAIT_GRANDCHILD", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "PATH_MAX", 
        "type": "macro", 
        "value": "260"
    }, 
    {
        "name": "CHAR_BIT", 
        "type": "macro", 
        "value": "8"
    }, 
    {
        "name": "SCHAR_MIN", 
        "type": "macro", 
        "value": "(-128)"
    }, 
    {
        "name": "SCHAR_MAX", 
        "type": "macro", 
        "value": "127"
    }, 
    {
        "name": "UCHAR_MAX", 
        "type": "macro", 
        "value": "255"
    }, 
    {
        "name": "CHAR_MIN", 
        "type": "macro", 
        "value": "SCHAR_MIN"
    }, 
    {
        "name": "CHAR_MAX", 
        "type": "macro", 
        "value": "SCHAR_MAX"
    }, 
    {
        "name": "MB_LEN_MAX", 
        "type": "macro", 
        "value": "5"
    }, 
    {
        "name": "SHRT_MIN", 
        "type": "macro", 
        "value": "(-32768)"
    }, 
    {
        "name": "SHRT_MAX", 
        "type": "macro", 
        "value": "32767"
    }, 
    {
        "name": "USHRT_MAX", 
        "type": "macro", 
        "value": "65535"
    }, 
    {
        "name": "INT_MIN", 
        "type": "macro", 
        "value": "((-2147483647) - 1)"
    }, 
    {
        "name": "INT_MAX", 
        "type": "macro", 
        "value": "2147483647"
    }, 
    {
        "name": "UINT_MAX", 
        "type": "macro", 
        "value": "4294967295L"
    }, 
    {
        "name": "LONG_MIN", 
        "type": "macro", 
        "value": "((-2147483647L) - 1)"
    }, 
    {
        "name": "LONG_MAX", 
        "type": "macro", 
        "value": "2147483647L"
    }, 
    {
        "name": "ULONG_MAX", 
        "type": "macro", 
        "value": "4294967295L"
    }, 
    {
        "name": "LLONG_MAX", 
        "type": "macro", 
        "value": "9223372036854775807L"
    }, 
    {
        "name": "LLONG_MIN", 
        "type": "macro", 
        "value": "((-9223372036854775807L) - 1)"
    }, 
    {
        "name": "ULLONG_MAX", 
        "type": "macro", 
        "value": "18446744073709551615L"
    }, 
    {
        "name": "_I8_MIN", 
        "type": "macro", 
        "value": "((-127) - 1)"
    }, 
    {
        "name": "_I8_MAX", 
        "type": "macro", 
        "value": "127"
    }, 
    {
        "name": "_UI8_MAX", 
        "type": "macro", 
        "value": "255"
    }, 
    {
        "name": "_I16_MIN", 
        "type": "macro", 
        "value": "((-32767) - 1)"
    }, 
    {
        "name": "_I16_MAX", 
        "type": "macro", 
        "value": "32767"
    }, 
    {
        "name": "_UI16_MAX", 
        "type": "macro", 
        "value": "65535"
    }, 
    {
        "name": "_I32_MIN", 
        "type": "macro", 
        "value": "((-2147483647) - 1)"
    }, 
    {
        "name": "_I32_MAX", 
        "type": "macro", 
        "value": "2147483647"
    }, 
    {
        "name": "_UI32_MAX", 
        "type": "macro", 
        "value": "4294967295L"
    }, 
    {
        "name": "_I64_MIN", 
        "type": "macro", 
        "value": "((-9223372036854775807L) - 1)"
    }, 
    {
        "name": "_I64_MAX", 
        "type": "macro", 
        "value": "9223372036854775807L"
    }, 
    {
        "name": "_UI64_MAX", 
        "type": "macro", 
        "value": "18446744073709551615L"
    }, 
    {
        "name": "SIZE_MAX", 
        "type": "macro", 
        "value": "_UI64_MAX"
    }, 
    {
        "name": "SSIZE_MAX", 
        "type": "macro", 
        "value": "_I64_MAX"
    }, 
    {
        "name": "CHAR_BIT", 
        "type": "macro", 
        "value": "__CHAR_BIT__"
    }, 
    {
        "name": "SCHAR_MIN", 
        "type": "macro", 
        "value": "((-SCHAR_MAX) - 1)"
    }, 
    {
        "name": "SCHAR_MAX", 
        "type": "macro", 
        "value": "__SCHAR_MAX__"
    }, 
    {
        "name": "UCHAR_MAX", 
        "type": "macro", 
        "value": "((SCHAR_MAX * 2) + 1)"
    }, 
    {
        "name": "CHAR_MIN", 
        "type": "macro", 
        "value": "SCHAR_MIN"
    }, 
    {
        "name": "CHAR_MAX", 
        "type": "macro", 
        "value": "SCHAR_MAX"
    }, 
    {
        "name": "SHRT_MIN", 
        "type": "macro", 
        "value": "((-SHRT_MAX) - 1)"
    }, 
    {
        "name": "SHRT_MAX", 
        "type": "macro", 
        "value": "__SHRT_MAX__"
    }, 
    {
        "name": "USHRT_MAX", 
        "type": "macro", 
        "value": "((SHRT_MAX * 2) + 1)"
    }, 
    {
        "name": "INT_MIN", 
        "type": "macro", 
        "value": "((-INT_MAX) - 1)"
    }, 
    {
        "name": "INT_MAX", 
        "type": "macro", 
        "value": "__INT_MAX__"
    }, 
    {
        "name": "UINT_MAX", 
        "type": "macro", 
        "value": "((INT_MAX * 2) + 1)"
    }, 
    {
        "name": "LONG_MIN", 
        "type": "macro", 
        "value": "((-LONG_MAX) - 1L)"
    }, 
    {
        "name": "LONG_MAX", 
        "type": "macro", 
        "value": "__LONG_MAX__"
    }, 
    {
        "name": "ULONG_MAX", 
        "type": "macro", 
        "value": "((LONG_MAX * 2L) + 1L)"
    }, 
    {
        "name": "LLONG_MIN", 
        "type": "macro", 
        "value": "((-LLONG_MAX) - 1L)"
    }, 
    {
        "name": "LLONG_MAX", 
        "type": "macro", 
        "value": "__LONG_LONG_MAX__"
    }, 
    {
        "name": "ULLONG_MAX", 
        "type": "macro", 
        "value": "((LLONG_MAX * 2L) + 1L)"
    }, 
    {
        "name": "LONG_LONG_MIN", 
        "type": "macro", 
        "value": "((-LONG_LONG_MAX) - 1L)"
    }, 
    {
        "name": "LONG_LONG_MAX", 
        "type": "macro", 
        "value": "__LONG_LONG_MAX__"
    }, 
    {
        "name": "ULONG_LONG_MAX", 
        "type": "macro", 
        "value": "((LONG_LONG_MAX * 2L) + 1L)"
    }, 
    {
        "name": "EXIT_SUCCESS", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "EXIT_FAILURE", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "ctype": {
            "Klass": "CtypesTypedef", 
            "errors": [], 
            "name": "_onexit_t"
        }, 
        "name": "onexit_t", 
        "type": "typedef"
    }, 
    {
        "args": [
            "x"
        ], 
        "body": "pointer((x.contents.ld))", 
        "name": "_PTR_LD", 
        "type": "macro_function"
    }, 
    {
        "name": "RAND_MAX", 
        "type": "macro", 
        "value": "32767"
    }, 
    {
        "args": [
            "a", 
            "b"
        ], 
        "body": "(a > b) and a or b", 
        "name": "__max", 
        "type": "macro_function"
    }, 
    {
        "args": [
            "a", 
            "b"
        ], 
        "body": "(a < b) and a or b", 
        "name": "__min", 
        "type": "macro_function"
    }, 
    {
        "name": "_MAX_PATH", 
        "type": "macro", 
        "value": "260"
    }, 
    {
        "name": "_MAX_DRIVE", 
        "type": "macro", 
        "value": "3"
    }, 
    {
        "name": "_MAX_DIR", 
        "type": "macro", 
        "value": "256"
    }, 
    {
        "name": "_MAX_FNAME", 
        "type": "macro", 
        "value": "256"
    }, 
    {
        "name": "_MAX_EXT", 
        "type": "macro", 
        "value": "256"
    }, 
    {
        "name": "_OUT_TO_DEFAULT", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "_OUT_TO_STDERR", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "_OUT_TO_MSGBOX", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "_REPORT_ERRMODE", 
        "type": "macro", 
        "value": "3"
    }, 
    {
        "name": "_WRITE_ABORT_MSG", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "_CALL_REPORTFAULT", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "_MAX_ENV", 
        "type": "macro", 
        "value": "32767"
    }, 
    {
        "name": "errno", 
        "type": "macro", 
        "value": "((_errno ())[0])"
    }, 
    {
        "name": "_doserrno", 
        "type": "macro", 
        "value": "((__doserrno ())[0])"
    }, 
    {
        "args": [
            "_Array"
        ], 
        "body": "(sizeof(_Array) / sizeof((_Array [0])))", 
        "name": "_countof", 
        "type": "macro_function"
    }, 
    {
        "name": "strtod", 
        "type": "macro", 
        "value": "__strtod"
    }, 
    {
        "name": "_CVTBUFSIZE", 
        "type": "macro", 
        "value": "(309 + 40)"
    }, 
    {
        "name": "sys_errlist", 
        "type": "macro", 
        "value": "_sys_errlist"
    }, 
    {
        "name": "sys_nerr", 
        "type": "macro", 
        "value": "_sys_nerr"
    }, 
    {
        "name": "_HEAP_MAXREQ", 
        "type": "macro", 
        "value": "18446744073709551584L"
    }, 
    {
        "name": "_HEAPEMPTY", 
        "type": "macro", 
        "value": "(-1)"
    }, 
    {
        "name": "_HEAPOK", 
        "type": "macro", 
        "value": "(-2)"
    }, 
    {
        "name": "_HEAPBADBEGIN", 
        "type": "macro", 
        "value": "(-3)"
    }, 
    {
        "name": "_HEAPBADNODE", 
        "type": "macro", 
        "value": "(-4)"
    }, 
    {
        "name": "_HEAPEND", 
        "type": "macro", 
        "value": "(-5)"
    }, 
    {
        "name": "_HEAPBADPTR", 
        "type": "macro", 
        "value": "(-6)"
    }, 
    {
        "name": "_FREEENTRY", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "_USEDENTRY", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "args": [
            "a"
        ], 
        "body": "(_aligned_free (a))", 
        "name": "_mm_free", 
        "type": "macro_function"
    }, 
    {
        "name": "_MAX_WAIT_MALLOC_CRT", 
        "type": "macro", 
        "value": "60000"
    }, 
    {
        "name": "_ALLOCA_S_THRESHOLD", 
        "type": "macro", 
        "value": "1024"
    }, 
    {
        "name": "_ALLOCA_S_STACK_MARKER", 
        "type": "macro", 
        "value": "52428"
    }, 
    {
        "name": "_ALLOCA_S_HEAP_MARKER", 
        "type": "macro", 
        "value": "56797"
    }, 
    {
        "name": "_ALLOCA_S_MARKER_SIZE", 
        "type": "macro", 
        "value": "16"
    }, 
    {
        "name": "_NLSCMPERROR", 
        "type": "macro", 
        "value": "2147483647"
    }, 
    {
        "name": "strcasecmp", 
        "type": "macro", 
        "value": "_stricmp"
    }, 
    {
        "name": "wcswcs", 
        "type": "macro", 
        "value": "wcsstr"
    }, 
    {
        "ctype": {
            "Klass": "CtypesSimple", 
            "errors": [], 
            "longs": 0, 
            "name": "_Bool", 
            "signed": true
        }, 
        "name": "bool", 
        "type": "typedef"
    }, 
    {
        "name": "true", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "false", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "__bool_true_false_are_defined", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "_threadid", 
        "type": "macro", 
        "value": "(__threadid ())"
    }, 
    {
        "name": "INT8_MIN", 
        "type": "macro", 
        "value": "(-128)"
    }, 
    {
        "name": "INT16_MIN", 
        "type": "macro", 
        "value": "(-32768)"
    }, 
    {
        "name": "INT32_MIN", 
        "type": "macro", 
        "value": "((-2147483647) - 1)"
    }, 
    {
        "name": "INT64_MIN", 
        "type": "macro", 
        "value": "((-9223372036854775807L) - 1)"
    }, 
    {
        "name": "INT8_MAX", 
        "type": "macro", 
        "value": "127"
    }, 
    {
        "name": "INT16_MAX", 
        "type": "macro", 
        "value": "32767"
    }, 
    {
        "name": "INT32_MAX", 
        "type": "macro", 
        "value": "2147483647"
    }, 
    {
        "name": "INT64_MAX", 
        "type": "macro", 
        "value": "9223372036854775807L"
    }, 
    {
        "name": "UINT8_MAX", 
        "type": "macro", 
        "value": "255"
    }, 
    {
        "name": "UINT16_MAX", 
        "type": "macro", 
        "value": "65535"
    }, 
    {
        "name": "UINT32_MAX", 
        "type": "macro", 
        "value": "4294967295L"
    }, 
    {
        "name": "UINT64_MAX", 
        "type": "macro", 
        "value": "18446744073709551615L"
    }, 
    {
        "name": "INT_LEAST8_MIN", 
        "type": "macro", 
        "value": "INT8_MIN"
    }, 
    {
        "name": "INT_LEAST16_MIN", 
        "type": "macro", 
        "value": "INT16_MIN"
    }, 
    {
        "name": "INT_LEAST32_MIN", 
        "type": "macro", 
        "value": "INT32_MIN"
    }, 
    {
        "name": "INT_LEAST64_MIN", 
        "type": "macro", 
        "value": "INT64_MIN"
    }, 
    {
        "name": "INT_LEAST8_MAX", 
        "type": "macro", 
        "value": "INT8_MAX"
    }, 
    {
        "name": "INT_LEAST16_MAX", 
        "type": "macro", 
        "value": "INT16_MAX"
    }, 
    {
        "name": "INT_LEAST32_MAX", 
        "type": "macro", 
        "value": "INT32_MAX"
    }, 
    {
        "name": "INT_LEAST64_MAX", 
        "type": "macro", 
        "value": "INT64_MAX"
    }, 
    {
        "name": "UINT_LEAST8_MAX", 
        "type": "macro", 
        "value": "UINT8_MAX"
    }, 
    {
        "name": "UINT_LEAST16_MAX", 
        "type": "macro", 
        "value": "UINT16_MAX"
    }, 
    {
        "name": "UINT_LEAST32_MAX", 
        "type": "macro", 
        "value": "UINT32_MAX"
    }, 
    {
        "name": "UINT_LEAST64_MAX", 
        "type": "macro", 
        "value": "UINT64_MAX"
    }, 
    {
        "name": "INT_FAST8_MIN", 
        "type": "macro", 
        "value": "INT8_MIN"
    }, 
    {
        "name": "INT_FAST16_MIN", 
        "type": "macro", 
        "value": "INT16_MIN"
    }, 
    {
        "name": "INT_FAST32_MIN", 
        "type": "macro", 
        "value": "INT32_MIN"
    }, 
    {
        "name": "INT_FAST64_MIN", 
        "type": "macro", 
        "value": "INT64_MIN"
    }, 
    {
        "name": "INT_FAST8_MAX", 
        "type": "macro", 
        "value": "INT8_MAX"
    }, 
    {
        "name": "INT_FAST16_MAX", 
        "type": "macro", 
        "value": "INT16_MAX"
    }, 
    {
        "name": "INT_FAST32_MAX", 
        "type": "macro", 
        "value": "INT32_MAX"
    }, 
    {
        "name": "INT_FAST64_MAX", 
        "type": "macro", 
        "value": "INT64_MAX"
    }, 
    {
        "name": "UINT_FAST8_MAX", 
        "type": "macro", 
        "value": "UINT8_MAX"
    }, 
    {
        "name": "UINT_FAST16_MAX", 
        "type": "macro", 
        "value": "UINT16_MAX"
    }, 
    {
        "name": "UINT_FAST32_MAX", 
        "type": "macro", 
        "value": "UINT32_MAX"
    }, 
    {
        "name": "UINT_FAST64_MAX", 
        "type": "macro", 
        "value": "UINT64_MAX"
    }, 
    {
        "name": "INTPTR_MIN", 
        "type": "macro", 
        "value": "INT64_MIN"
    }, 
    {
        "name": "INTPTR_MAX", 
        "type": "macro", 
        "value": "INT64_MAX"
    }, 
    {
        "name": "UINTPTR_MAX", 
        "type": "macro", 
        "value": "UINT64_MAX"
    }, 
    {
        "name": "INTMAX_MIN", 
        "type": "macro", 
        "value": "INT64_MIN"
    }, 
    {
        "name": "INTMAX_MAX", 
        "type": "macro", 
        "value": "INT64_MAX"
    }, 
    {
        "name": "UINTMAX_MAX", 
        "type": "macro", 
        "value": "UINT64_MAX"
    }, 
    {
        "name": "PTRDIFF_MIN", 
        "type": "macro", 
        "value": "INT64_MIN"
    }, 
    {
        "name": "PTRDIFF_MAX", 
        "type": "macro", 
        "value": "INT64_MAX"
    }, 
    {
        "name": "SIG_ATOMIC_MIN", 
        "type": "macro", 
        "value": "INT32_MIN"
    }, 
    {
        "name": "SIG_ATOMIC_MAX", 
        "type": "macro", 
        "value": "INT32_MAX"
    }, 
    {
        "name": "WCHAR_MIN", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "WCHAR_MAX", 
        "type": "macro", 
        "value": "65535"
    }, 
    {
        "name": "WINT_MIN", 
        "type": "macro", 
        "value": "0"
    }, 
    {
        "name": "WINT_MAX", 
        "type": "macro", 
        "value": "65535"
    }, 
    {
        "args": [
            "val"
        ], 
        "body": "((INT_LEAST8_MAX - INT_LEAST8_MAX) + val)", 
        "name": "INT8_C", 
        "type": "macro_function"
    }, 
    {
        "args": [
            "val"
        ], 
        "body": "((INT_LEAST16_MAX - INT_LEAST16_MAX) + val)", 
        "name": "INT16_C", 
        "type": "macro_function"
    }, 
    {
        "args": [
            "val"
        ], 
        "body": "((INT_LEAST32_MAX - INT_LEAST32_MAX) + val)", 
        "name": "INT32_C", 
        "type": "macro_function"
    }, 
    {
        "args": [
            "val"
        ], 
        "body": "val", 
        "name": "UINT8_C", 
        "type": "macro_function"
    }, 
    {
        "args": [
            "val"
        ], 
        "body": "val", 
        "name": "UINT16_C", 
        "type": "macro_function"
    }, 
    {
        "name": "_DOMAIN", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "_SING", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "_OVERFLOW", 
        "type": "macro", 
        "value": "3"
    }, 
    {
        "name": "_UNDERFLOW", 
        "type": "macro", 
        "value": "4"
    }, 
    {
        "name": "_TLOSS", 
        "type": "macro", 
        "value": "5"
    }, 
    {
        "name": "_PLOSS", 
        "type": "macro", 
        "value": "6"
    }, 
    {
        "name": "DOMAIN", 
        "type": "macro", 
        "value": "_DOMAIN"
    }, 
    {
        "name": "SING", 
        "type": "macro", 
        "value": "_SING"
    }, 
    {
        "name": "OVERFLOW", 
        "type": "macro", 
        "value": "_OVERFLOW"
    }, 
    {
        "name": "UNDERFLOW", 
        "type": "macro", 
        "value": "_UNDERFLOW"
    }, 
    {
        "name": "TLOSS", 
        "type": "macro", 
        "value": "_TLOSS"
    }, 
    {
        "name": "PLOSS", 
        "type": "macro", 
        "value": "_PLOSS"
    }, 
    {
        "name": "M_E", 
        "type": "macro", 
        "value": "2.718281828459045"
    }, 
    {
        "name": "M_LOG2E", 
        "type": "macro", 
        "value": "1.4426950408889634"
    }, 
    {
        "name": "M_LOG10E", 
        "type": "macro", 
        "value": "0.4342944819032518"
    }, 
    {
        "name": "M_LN2", 
        "type": "macro", 
        "value": "0.6931471805599453"
    }, 
    {
        "name": "M_LN10", 
        "type": "macro", 
        "value": "2.302585092994046"
    }, 
    {
        "name": "M_PI", 
        "type": "macro", 
        "value": "3.141592653589793"
    }, 
    {
        "name": "M_PI_2", 
        "type": "macro", 
        "value": "1.5707963267948966"
    }, 
    {
        "name": "M_PI_4", 
        "type": "macro", 
        "value": "0.7853981633974483"
    }, 
    {
        "name": "M_1_PI", 
        "type": "macro", 
        "value": "0.3183098861837907"
    }, 
    {
        "name": "M_2_PI", 
        "type": "macro", 
        "value": "0.6366197723675814"
    }, 
    {
        "name": "M_2_SQRTPI", 
        "type": "macro", 
        "value": "1.1283791670955126"
    }, 
    {
        "name": "M_SQRT2", 
        "type": "macro", 
        "value": "1.4142135623730951"
    }, 
    {
        "name": "M_SQRT1_2", 
        "type": "macro", 
        "value": "0.7071067811865476"
    }, 
    {
        "name": "__MINGW_FPCLASS_DEFINED", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "_FPCLASS_SNAN", 
        "type": "macro", 
        "value": "1"
    }, 
    {
        "name": "_FPCLASS_QNAN", 
        "type": "macro", 
        "value": "2"
    }, 
    {
        "name": "_FPCLASS_NINF", 
        "type": "macro", 
        "value": "4"
    }, 
    {
        "name": "_FPCLASS_NN", 
        "type": "macro", 
        "value": "8"
    }, 
    {
        "name": "_FPCLASS_ND", 
        "type": "macro", 
        "value": "16"
    }, 
    {
        "name": "_FPCLASS_NZ", 
        "type": "macro", 
        "value": "32"
    }, 
    {
        "name": "_FPCLASS_PZ", 
        "type": "macro", 
        "value": "64"
    }, 
    {
        "name": "_FPCLASS_PD", 
        "type": "macro", 
        "value": "128"
    }, 
    {
        "name": "_FPCLASS_PN", 
        "type": "macro", 
        "value": "256"
    }, 
    {
        "name": "_FPCLASS_PINF", 
        "type": "macro", 
        "value": "512"
    }, 
    {
        "name": "__setusermatherr", 
        "type": "macro", 
        "value": "__mingw_setusermatherr"
    }, 
    {
        "name": "EDOM", 
        "type": "macro", 
        "value": "33"
    }, 
    {
        "name": "ERANGE", 
        "type": "macro", 
        "value": "34"
    }, 
    {
        "name": "FP_SNAN", 
        "type": "macro", 
        "value": "_FPCLASS_SNAN"
    }, 
    {
        "name": "FP_QNAN", 
        "type": "macro", 
        "value": "_FPCLASS_QNAN"
    }, 
    {
        "name": "FP_NINF", 
        "type": "macro", 
        "value": "_FPCLASS_NINF"
    }, 
    {
        "name": "FP_PINF", 
        "type": "macro", 
        "value": "_FPCLASS_PINF"
    }, 
    {
        "name": "FP_NDENORM", 
        "type": "macro", 
        "value": "_FPCLASS_ND"
    }, 
    {
        "name": "FP_PDENORM", 
        "type": "macro", 
        "value": "_FPCLASS_PD"
    }, 
    {
        "name": "FP_NZERO", 
        "type": "macro", 
        "value": "_FPCLASS_NZ"
    }, 
    {
        "name": "FP_PZERO", 
        "type": "macro", 
        "value": "_FPCLASS_PZ"
    }, 
    {
        "name": "FP_NNORM", 
        "type": "macro", 
        "value": "_FPCLASS_NN"
    }, 
    {
        "name": "FP_PNORM", 
        "type": "macro", 
        "value": "_FPCLASS_PN"
    }, 
    {
        "name": "HUGE_VALF", 
        "type": "macro", 
        "value": "__INFF"
    }, 
    {
        "name": "INFINITY", 
        "type": "macro", 
        "value": "HUGE_VALF"
    }, 
    {
        "name": "NAN", 
        "type": "macro", 
        "value": "__QNAN"
    }, 
    {
        "name": "FP_NAN", 
        "type": "macro", 
        "value": "256"
    }, 
    {
        "name": "FP_NORMAL", 
        "type": "macro", 
        "value": "1024"
    }, 
    {
        "name": "FP_INFINITE", 
        "type": "macro", 
        "value": "(FP_NAN | FP_NORMAL)"
    }, 
    {
        "name": "FP_ZERO", 
        "type": "macro", 
        "value": "16384"
    }, 
    {
        "name": "FP_SUBNORMAL", 
        "type": "macro", 
        "value": "(FP_NORMAL | FP_ZERO)"
    }, 
    {
        "args": [
            "__call", 
            "__fin", 
            "x"
        ], 
        "body": "__fin", 
        "name": "__dfp_expansion", 
        "type": "macro_function"
    }, 
    {
        "name": "FP_ILOGB0", 
        "type": "macro", 
        "value": "2147483648L"
    }, 
    {
        "name": "FP_ILOGBNAN", 
        "type": "macro", 
        "value": "2147483648L"
    }, 
    {
        "name": "_nan", 
        "type": "macro", 
        "value": "(nan (''))"
    }, 
    {
        "name": "_nanf", 
        "type": "macro", 
        "value": "(nanf (''))"
    }, 
    {
        "name": "matherr", 
        "type": "macro", 
        "value": "_matherr"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "refcount", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }
                ], 
                [
                    "lc_codepage", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": false
                    }
                ], 
                [
                    "lc_collate_cp", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": false
                    }
                ], 
                [
                    "lc_handle", 
                    {
                        "Klass": "CtypesArray", 
                        "base": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 1, 
                            "name": "int", 
                            "signed": false
                        }, 
                        "count": {
                            "Klass": "ConstantExpressionNode", 
                            "errors": [], 
                            "value": 6
                        }, 
                        "errors": []
                    }
                ], 
                [
                    "lc_id", 
                    {
                        "Klass": "CtypesArray", 
                        "base": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "LC_ID"
                        }, 
                        "count": {
                            "Klass": "ConstantExpressionNode", 
                            "errors": [], 
                            "value": 6
                        }, 
                        "errors": []
                    }
                ], 
                [
                    "lc_category", 
                    {
                        "Klass": "CtypesArray", 
                        "base": {
                            "Klass": "CtypesStruct", 
                            "anonymous": true, 
                            "errors": [], 
                            "members": [
                                [
                                    "locale", 
                                    {
                                        "Klass": "CtypesSpecial", 
                                        "errors": [], 
                                        "name": "String"
                                    }
                                ], 
                                [
                                    "wlocale", 
                                    {
                                        "Klass": "CtypesPointer", 
                                        "destination": {
                                            "Klass": "CtypesTypedef", 
                                            "errors": [], 
                                            "name": "wchar_t"
                                        }, 
                                        "errors": [], 
                                        "qualifiers": []
                                    }
                                ], 
                                [
                                    "refcount", 
                                    {
                                        "Klass": "CtypesPointer", 
                                        "destination": {
                                            "Klass": "CtypesSimple", 
                                            "errors": [], 
                                            "longs": 0, 
                                            "name": "int", 
                                            "signed": true
                                        }, 
                                        "errors": [], 
                                        "qualifiers": []
                                    }
                                ], 
                                [
                                    "wrefcount", 
                                    {
                                        "Klass": "CtypesPointer", 
                                        "destination": {
                                            "Klass": "CtypesSimple", 
                                            "errors": [], 
                                            "longs": 0, 
                                            "name": "int", 
                                            "signed": true
                                        }, 
                                        "errors": [], 
                                        "qualifiers": []
                                    }
                                ]
                            ], 
                            "opaque": false, 
                            "src": [
                                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                                450
                            ], 
                            "tag": "anon_1", 
                            "variety": "struct"
                        }, 
                        "count": {
                            "Klass": "ConstantExpressionNode", 
                            "errors": [], 
                            "value": 6
                        }, 
                        "errors": []
                    }
                ], 
                [
                    "lc_clike", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }
                ], 
                [
                    "mb_cur_max", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }
                ], 
                [
                    "lconv_intl_refcount", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "int", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "lconv_num_refcount", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "int", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "lconv_mon_refcount", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "int", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "lconv", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesStruct", 
                            "anonymous": false, 
                            "errors": [], 
                            "members": null, 
                            "opaque": true, 
                            "src": [
                                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                                461
                            ], 
                            "tag": "lconv", 
                            "variety": "struct"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "ctype1_refcount", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "int", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "ctype1", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "short", 
                            "signed": false
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "pctype", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "short", 
                            "signed": false
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "pclmap", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "char", 
                            "signed": false
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "pcumap", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "char", 
                            "signed": false
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "lc_time_curr", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesStruct", 
                            "anonymous": false, 
                            "errors": [], 
                            "members": null, 
                            "opaque": true, 
                            "src": [
                                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                                467
                            ], 
                            "tag": "__lc_time_data", 
                            "variety": "struct"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                444
            ], 
            "tag": "threadlocaleinfostruct", 
            "variety": "struct"
        }, 
        "name": "threadlocaleinfostruct", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": null, 
            "opaque": true, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                423
            ], 
            "tag": "threadmbcinfostruct", 
            "variety": "struct"
        }, 
        "name": "threadmbcinfostruct", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": null, 
            "opaque": true, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                426
            ], 
            "tag": "__lc_time_data", 
            "variety": "struct"
        }, 
        "name": "__lc_time_data", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "locinfo", 
                    {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "pthreadlocinfo"
                    }
                ], 
                [
                    "mbcinfo", 
                    {
                        "Klass": "CtypesTypedef", 
                        "errors": [], 
                        "name": "pthreadmbcinfo"
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                428
            ], 
            "tag": "localeinfo_struct", 
            "variety": "struct"
        }, 
        "name": "localeinfo_struct", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "wLanguage", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "short", 
                        "signed": false
                    }
                ], 
                [
                    "wCountry", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "short", 
                        "signed": false
                    }
                ], 
                [
                    "wCodePage", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "short", 
                        "signed": false
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                435
            ], 
            "tag": "tagLC_ID", 
            "variety": "struct"
        }, 
        "name": "tagLC_ID", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": null, 
            "opaque": true, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/crtdefs.h", 
                461
            ], 
            "tag": "lconv", 
            "variety": "struct"
        }, 
        "name": "lconv", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "_ptr", 
                    {
                        "Klass": "CtypesSpecial", 
                        "errors": [], 
                        "name": "String"
                    }
                ], 
                [
                    "_cnt", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }
                ], 
                [
                    "_base", 
                    {
                        "Klass": "CtypesSpecial", 
                        "errors": [], 
                        "name": "String"
                    }
                ], 
                [
                    "_flag", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }
                ], 
                [
                    "_file", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }
                ], 
                [
                    "_charbuf", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }
                ], 
                [
                    "_bufsiz", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }
                ], 
                [
                    "_tmpfname", 
                    {
                        "Klass": "CtypesSpecial", 
                        "errors": [], 
                        "name": "String"
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/stdio.h", 
                26
            ], 
            "tag": "_iobuf", 
            "variety": "struct"
        }, 
        "name": "_iobuf", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "quot", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }
                ], 
                [
                    "rem", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/stdlib.h", 
                50
            ], 
            "tag": "_div_t", 
            "variety": "struct"
        }, 
        "name": "_div_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "quot", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 1, 
                        "name": "int", 
                        "signed": true
                    }
                ], 
                [
                    "rem", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 1, 
                        "name": "int", 
                        "signed": true
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/stdlib.h", 
                55
            ], 
            "tag": "_ldiv_t", 
            "variety": "struct"
        }, 
        "name": "_ldiv_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "type", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": true
                    }
                ], 
                [
                    "name", 
                    {
                        "Klass": "CtypesSpecial", 
                        "errors": [], 
                        "name": "String"
                    }
                ], 
                [
                    "arg1", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }
                ], 
                [
                    "arg2", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }
                ], 
                [
                    "retval", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/math.h", 
                168
            ], 
            "tag": "_exception", 
            "variety": "struct"
        }, 
        "name": "_exception", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "x", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "float", 
                        "signed": true
                    }
                ], 
                [
                    "val", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "int", 
                        "signed": false
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/math.h", 
                127
            ], 
            "tag": "__mingw_flt_type_t", 
            "variety": "union"
        }, 
        "name": "__mingw_flt_type_t", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "x", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }
                ], 
                [
                    "y", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:/TDM-GCC-64/x86_64-w64-mingw32/include/math.h", 
                266
            ], 
            "tag": "_complex", 
            "variety": "struct"
        }, 
        "name": "_complex", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "ptr", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "seed", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_rng"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "seed", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "norm", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_rng"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "fill_norm", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_rng"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "n", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }, 
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesSimple", 
                                    "errors": [], 
                                    "longs": 0, 
                                    "name": "double", 
                                    "signed": true
                                }, 
                                "errors": [], 
                                "identifier": "x", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "nbytes", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_rng"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "free", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_rng"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                112
            ], 
            "tag": "sd_rng", 
            "variety": "struct"
        }, 
        "name": "sd_rng", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "ptr", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "apply", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hfill"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "n", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }, 
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesSimple", 
                                    "errors": [], 
                                    "longs": 0, 
                                    "name": "double", 
                                    "signed": true
                                }, 
                                "errors": [], 
                                "identifier": "t", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesSimple", 
                                    "errors": [], 
                                    "longs": 0, 
                                    "name": "uint32_t", 
                                    "signed": true
                                }, 
                                "errors": [], 
                                "identifier": "indices", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesSimple", 
                                    "errors": [], 
                                    "longs": 0, 
                                    "name": "double", 
                                    "signed": true
                                }, 
                                "errors": [], 
                                "identifier": "buf", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_stat"
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "free", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hfill"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                159
            ], 
            "tag": "sd_hfill", 
            "variety": "struct"
        }, 
        "name": "sd_hfill", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "ptr", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "get_maxvi", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_vi2i", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "vi", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_nu", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "h", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "free", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "h", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "fill", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "h", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hfill"
                                }, 
                                "errors": [], 
                                "identifier": "filler", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_stat"
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "h", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "t", 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesSimple", 
                                    "errors": [], 
                                    "longs": 0, 
                                    "name": "double", 
                                    "signed": true
                                }, 
                                "errors": [], 
                                "identifier": "aff", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "set", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "h", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "t", 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesSimple", 
                                    "errors": [], 
                                    "longs": 0, 
                                    "name": "double", 
                                    "signed": true
                                }, 
                                "errors": [], 
                                "identifier": "eff", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "nbytes", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "h", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_buf_lin", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "h", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "index", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_nd", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "h", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_t", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "h", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_dt", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "h", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_lim", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "h", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "i", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_len", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "h", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "i", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_pos", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "h", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "i", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_uvi", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "h", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "i", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_maxd", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "h", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "i", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_vi", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "h", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "i", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_vd", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "h", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "i", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "buf_is_null", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "h", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "_Bool", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                197
            ], 
            "tag": "sd_hist", 
            "variety": "struct"
        }, 
        "name": "sd_hist", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "nx", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }
                ], 
                [
                    "nc", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }
                ], 
                [
                    "id", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "uint32_t", 
                        "signed": true
                    }
                ], 
                [
                    "t", 
                    {
                        "Klass": "CtypesSimple", 
                        "errors": [], 
                        "longs": 0, 
                        "name": "double", 
                        "signed": true
                    }
                ], 
                [
                    "x", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "i", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "hist", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_hist"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "rng", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_rng"
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                453
            ], 
            "tag": "sd_sys_in", 
            "variety": "struct"
        }, 
        "name": "sd_sys_in", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "f", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "g", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "o", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                460
            ], 
            "tag": "sd_sys_out", 
            "variety": "struct"
        }, 
        "name": "sd_sys_out", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "ndim", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sys"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "ndc", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sys"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "nobs", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sys"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "nrpar", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sys"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "nipar", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sys"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "apply", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sys"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sys_in"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sys_out"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_stat"
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "free", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sys"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "ptr", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                470
            ], 
            "tag": "sd_sys", 
            "variety": "struct"
        }, 
        "name": "sd_sys", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "ptr", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "sys", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sys_exc"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys"
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_a", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sys_exc"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "set_a", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sys_exc"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "new_a", 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_tau", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sys_exc"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "set_tau", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sys_exc"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "new_tau", 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_D", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sys_exc"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "set_D", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sys_exc"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "new_D", 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_k", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sys_exc"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "set_k", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sys_exc"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "new_k", 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                533
            ], 
            "tag": "sd_sys_exc", 
            "variety": "struct"
        }, 
        "name": "sd_sys_exc", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "ptr", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "sys", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys"
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "free", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_n", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "net", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_m", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "net", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_nnz", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "net", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_or", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "net", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_or_i", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "net", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "i", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_ic", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "net", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_ic_i", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "net", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "i", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_w", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "net", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_w_i", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "net", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "i", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_d", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "net", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_d_i", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "net", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "i", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_ns", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "net", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_ne", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "net", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "cn_is_null", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "net", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "_Bool", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_Ms_i", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "net", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "i", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_Ma_i", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "net", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "i", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_Me_i", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "net", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "i", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_M_i", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "net", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "i", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_models_i", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "net", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "i", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_sys"
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get__init1", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_net"
                                }, 
                                "errors": [], 
                                "identifier": "net", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "_Bool", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                649
            ], 
            "tag": "sd_net", 
            "variety": "struct"
        }, 
        "name": "sd_net", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "ptr", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "free", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "apply", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "t", 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "nx", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }, 
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesSimple", 
                                    "errors": [], 
                                    "longs": 0, 
                                    "name": "double", 
                                    "signed": true
                                }, 
                                "errors": [], 
                                "identifier": "x", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "nc", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }, 
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesSimple", 
                                    "errors": [], 
                                    "longs": 0, 
                                    "name": "double", 
                                    "signed": true
                                }, 
                                "errors": [], 
                                "identifier": "c", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_stat"
                        }, 
                        "variadic": false
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                872
            ], 
            "tag": "sd_out", 
            "variety": "struct"
        }, 
        "name": "sd_out", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "ptr", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "out", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_file"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out"
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "is_std", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_file"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "_Bool", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_fd", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_file"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "FILE"
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                913
            ], 
            "tag": "sd_out_file", 
            "variety": "struct"
        }, 
        "name": "sd_out_file", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "ptr", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "out", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_mem"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out"
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_nx", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_mem"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_nc", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_mem"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_n_sample", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_mem"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_capacity", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_mem"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_xs", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_mem"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_cs", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_mem"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                964
            ], 
            "tag": "sd_out_mem", 
            "variety": "struct"
        }, 
        "name": "sd_out_mem", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "ptr", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "out", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_tee"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out"
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_nout", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_tee"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "outs_is_null", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_tee"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "_Bool", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "set_out", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_tee"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "i", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }, 
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out"
                                }, 
                                "errors": [], 
                                "identifier": "out", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_stat"
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_out", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_tee"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "i", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out"
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                1035
            ], 
            "tag": "sd_out_tee", 
            "variety": "struct"
        }, 
        "name": "sd_out_tee", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "ptr", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "out", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_tavg"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out"
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_len", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_tavg"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_pos", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_tavg"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_t", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_tavg"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_out", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_tavg"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out"
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_x", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_tavg"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_c", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_tavg"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                1096
            ], 
            "tag": "sd_out_tavg", 
            "variety": "struct"
        }, 
        "name": "sd_out_tavg", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "ptr", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "out", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_sfilt"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out"
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_nfilt", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_sfilt"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_filtlen", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_sfilt"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_xfilts", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_sfilt"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_cfilts", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_sfilt"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_x", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_sfilt"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_c", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_sfilt"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_out", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_out_sfilt"
                                }, 
                                "errors": [], 
                                "identifier": "d", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_out"
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                1152
            ], 
            "tag": "sd_out_sfilt", 
            "variety": "struct"
        }, 
        "name": "sd_out_sfilt", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "ptr", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "get_nx", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sch"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "apply", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sch"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_hist"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_rng"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sys"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "t", 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "dt", 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "nx", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }, 
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesSimple", 
                                    "errors": [], 
                                    "longs": 0, 
                                    "name": "double", 
                                    "signed": true
                                }, 
                                "errors": [], 
                                "identifier": "x", 
                                "qualifiers": []
                            }, 
                            {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "identifier": "nc", 
                                "longs": 0, 
                                "name": "uint32_t", 
                                "signed": true
                            }, 
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesSimple", 
                                    "errors": [], 
                                    "longs": 0, 
                                    "name": "double", 
                                    "signed": true
                                }, 
                                "errors": [], 
                                "identifier": "c", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_stat"
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "free", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sch"
                                }, 
                                "errors": [], 
                                "identifier": "", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                1234
            ], 
            "tag": "sd_sch", 
            "variety": "struct"
        }, 
        "name": "sd_sch", 
        "type": "typedef"
    }, 
    {
        "ctype": {
            "Klass": "CtypesStruct", 
            "anonymous": false, 
            "errors": [], 
            "members": [
                [
                    "ptr", 
                    {
                        "Klass": "CtypesPointer", 
                        "destination": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "errors": [], 
                        "qualifiers": []
                    }
                ], 
                [
                    "free", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sol"
                                }, 
                                "errors": [], 
                                "identifier": "s", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "void", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "cont", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sol"
                                }, 
                                "errors": [], 
                                "identifier": "s", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesTypedef", 
                            "errors": [], 
                            "name": "sd_stat"
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_nx", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sol"
                                }, 
                                "errors": [], 
                                "identifier": "s", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_nce", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sol"
                                }, 
                                "errors": [], 
                                "identifier": "s", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_nca", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sol"
                                }, 
                                "errors": [], 
                                "identifier": "s", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "uint32_t", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_hist", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sol"
                                }, 
                                "errors": [], 
                                "identifier": "s", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_hist"
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_rng", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sol"
                                }, 
                                "errors": [], 
                                "identifier": "s", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesTypedef", 
                                "errors": [], 
                                "name": "sd_rng"
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_t", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sol"
                                }, 
                                "errors": [], 
                                "identifier": "s", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesSimple", 
                            "errors": [], 
                            "longs": 0, 
                            "name": "double", 
                            "signed": true
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_x", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sol"
                                }, 
                                "errors": [], 
                                "identifier": "s", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ], 
                [
                    "get_c", 
                    {
                        "Klass": "CtypesFunction", 
                        "argtypes": [
                            {
                                "Klass": "CtypesPointer", 
                                "destination": {
                                    "Klass": "CtypesTypedef", 
                                    "errors": [], 
                                    "name": "sd_sol"
                                }, 
                                "errors": [], 
                                "identifier": "s", 
                                "qualifiers": []
                            }
                        ], 
                        "errors": [], 
                        "restype": {
                            "Klass": "CtypesPointer", 
                            "destination": {
                                "Klass": "CtypesSimple", 
                                "errors": [], 
                                "longs": 0, 
                                "name": "double", 
                                "signed": true
                            }, 
                            "errors": [], 
                            "qualifiers": []
                        }, 
                        "variadic": false
                    }
                ]
            ], 
            "opaque": false, 
            "src": [
                "C:\\\\Users\\\\mw\\\\Desktop\\\\sddekit\\\\src\\\\sddekit.h", 
                1349
            ], 
            "tag": "sd_sol", 
            "variety": "struct"
        }, 
        "name": "sd_sol", 
        "type": "typedef"
    }
]
