@ECHO OFF

SET SolutionDir=%1
SET PlatformType=%2
SET TargetDir=%3

REM SDL DLLs
copy /Y /B /V "%SolutionDir%ThirdParty\SDL2-2.0.12\lib\%PlatformType%\SDL2.dll" "%TargetDir%SDL2.dll"

REM SDL Font Library DLLs
copy /Y /B /V "%SolutionDir%ThirdParty\SDL2_ttf-2.0.15\lib\%PlatformType%\SDL2_ttf.dll" "%TargetDir%SDL2_ttf.dll"
copy /Y /B /V "%SolutionDir%ThirdParty\SDL2_ttf-2.0.15\lib\%PlatformType%\libfreetype-6.dll" "%TargetDir%libfreetype-6.dll"
copy /Y /B /V "%SolutionDir%ThirdParty\SDL2_ttf-2.0.15\lib\%PlatformType%\zlib1.dll" "%TargetDir%zlib1.dll"

REM SDL Image Library DLLs
copy /Y /B /V "%SolutionDir%ThirdParty\SDL2_image-2.0.5\lib\%PlatformType%\libjpeg-9.dll" "%TargetDir%libjpeg-9.dll"
copy /Y /B /V "%SolutionDir%ThirdParty\SDL2_image-2.0.5\lib\%PlatformType%\libpng16-16.dll" "%TargetDir%libpng16-16.dll"
copy /Y /B /V "%SolutionDir%ThirdParty\SDL2_image-2.0.5\lib\%PlatformType%\libtiff-5.dll" "%TargetDir%libtiff-5.dll"
copy /Y /B /V "%SolutionDir%ThirdParty\SDL2_image-2.0.5\lib\%PlatformType%\libwebp-7.dll" "%TargetDir%libwebp-7.dll"
copy /Y /B /V "%SolutionDir%ThirdParty\SDL2_image-2.0.5\lib\%PlatformType%\SDL2_image.dll" "%TargetDir%SDL2_image.dll"
