#!/bin/bash

jarsigner -verbose -storepass 123456 -sigalg SHA1withRSA -digestalg SHA1 -keystore gincu.keystore -signedjar bin/gincu-release-signed.apk bin/gincu-release-unsigned.apk gincu.keystore
zipalign -f -p 4 bin/gincu-release-signed.apk bin/gincu-release.apk
