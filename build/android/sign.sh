#!/bin/bash

echo Password is 123456
jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore gincu.keystore -signedjar bin/gincu-release-signed.apk bin/gincu-release-unsigned.apk gincu.keystore
zipalign -f -p 4 bin/gincu-release-signed.apk bin/gincu-release.apk
