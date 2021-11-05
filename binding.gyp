{
  'targets': [
    {
      'target_name': 'npmpackage',
      'sources': [
        "source/addon.cpp"
     ],
      "cflags!": [ "-fno-exceptions", "-frtti" ],
      "cflags_cc!": [ "-fno-exceptions", "-frtti" ],
      "cflags_cc": [ "-std=c++17", "-frtti" ],
      "conditions": [
        ['OS=="mac"', {
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            "OTHER_CFLAGS": [ "-std=c++17", "-frtti" ],
            "MACOSX_DEPLOYMENT_TARGET": "10.14.6"
          }
        }],
        ['OS=="win"', {
          "msvs_settings": {
            "VCCLCompilerTool": {
              "AdditionalOptions": [ "-std:c++17", "/EHsc", "/GR", "/permissive-" ],
            },
          },
        }]
      ],
      'include_dirs': [
        "<!(node -p \"require('node-addon-api').include_dir\")",
      ]
    }
  ]
}
