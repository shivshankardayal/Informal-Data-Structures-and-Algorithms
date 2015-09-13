html:
	xsltproc --xinclude --stringparam html.stylesheet "../css/bootstrap.min.css ../css/bootstrap-responsive.min.css ../css/styled.min.css" --path "src css" --output build/ html.xsl dsa.xml
#	perl -pi -e "s/\.pdf\"/\.png\"/g;" src/*.xml
	find . -name "*.html" | xargs perl -pi -e "s/<html>/<!DOCTYPE html>/g;"
	cp -r images build/
	./domp.py
	cp -r build/* /var/www/dsa/


pdf: src/*.xml dblatex.xsl Makefile
	rm -rf pdf
	cp -r src pdf	
	perl -pi -e "s/\.png\"/\.pdf\"/g;" pdf/*.xml	
	dblatex -bxetex -T db2latex -p dblatex.xsl -P preface.tocdepth="1" pdf/dsa.xml

latex:
	dblatex -bxetex -T db2latex -p dblatex.xsl -P preface.tocdepth="1" -t tex src/dsa.xml
	cd src && perl -pi -e "s/\.png/\.pdf/g;" dsa.tex

fop: src/*.xml fop.xsl Makefile
#	cd src && xmllint --xinclude c.xml>resolvedc.xml
	xsltproc --xinclude --output src/dsa.fo fop.xsl src/dsa.xml
	perl -pi -e "s/png/pdf/g;" src/dsa.fo
#	./fop.py
#	perl -pi -e "s/<html><body>//g;" src/c.fo
#	perl -pi -e "s/<\/body><\/html>//g;" src/c.fo
	cd src && fop dsa.fo dsa.pdf 
