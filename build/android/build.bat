@echo off

call ndk-build
if errorlevel 1 goto err

call ant %1
if errorlevel 1 goto err
call sh sign.sh
if errorlevel 1 goto err

goto end

:err
echo Error occurred!

:end
