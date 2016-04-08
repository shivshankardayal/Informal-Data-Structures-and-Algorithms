html: src/*.xml html.xsl Makefile domp.py
	xsltproc --xinclude --stringparam html.stylesheet "../css/bootstrap.min.css ../css/bootstrap-responsive.min.css ../css/styled.min.css" --path "src css" --output build/ html.xsl dsa.xml
#	perl -pi -e "s/\.pdf\"/\.png\"/g;" src/*.xml
	find . -name "*.html" | xargs perl -pi -e "s/<html>/<!DOCTYPE html>/g;"
	cp -r images build/
	./domp.py
	cp -r build/* /var/www/dsa/
#	cp -r build/* /opt/local/share/nginx/html/dsa/

p: src/*.xml dblatex.xsl Makefile
	rm -rf pdf
	cp -r src pdf	
	perl -pi -e "s/\.png\"/\.pdf\"/g;" pdf/*.xml	
	dblatex -bxetex -T db2latex -p dblatex.xsl -P preface.tocdepth="1" pdf/dsa.xml

latex:
	rm -rf pdf
	cp -r src pdf	
	dblatex -bxetex -T db2latex -p dblatex.xsl -P preface.tocdepth="1" -t tex src/dsa.xml -o pdf/dsa.tex
	perl -pi -e "s/\.png/\.pdf/g;" pdf/dsa.tex
	./lstlisting_to_minted.sh
	cd pdf && xelatex -shell-escape dsa.tex && xelatex -shell-escape dsa.tex

fop: src/*.xml fop.xsl Makefile
#	cd src && xmllint --xinclude c.xml>resolvedc.xml
	rm -rf pdf
	cp -r src pdf	
	perl -pi -e "s/\.png\"/\.pdf\"/g;" pdf/*.xml	
	xsltproc --xinclude --output pdf/dsa.fo fop.xsl pdf/dsa.xml
	perl -pi -e "s/png/pdf/g;" pdf/dsa.fo
#	./fop.py
#	perl -pi -e "s/<html><body>//g;" src/c.fo
#	perl -pi -e "s/<\/body><\/html>//g;" src/c.fo
	cd pdf && fop dsa.fo dsa.pdf 

clean:
	rm -rf pdf/* build/*

epub: src/*.xml epub.xsl Makefile
	xsltproc --xinclude --stringparam html.stylesheet "../css/bootstrap.min.css ../css/bootstrap-responsive.min.css ../css/epub.min.css" --path "src css" epub.xsl dsa.xml
	cp -r images OEBPS
	./epub.py
	zip -r dsa.epub mimetype css META-INF/ OEBPS/
