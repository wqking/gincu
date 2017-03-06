CPGF=/projects/cpgf
METAGEN=$CPGF/tools/metagen/
java -cp "$METAGEN/tool/bin;$METAGEN/js.jar" metagen --config config.gincu.js --xml xml/index.xml
