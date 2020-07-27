debug: format check build
	@./dyvo

build:
	@gcc -o dyvo -Wall *.c -lmd4c -lcairo

check:
	@cppcheck --suppress=missingIncludeSystem --template=gcc \
	          --quiet --platform=unix64 --enable=all *.c

format:
	@astyle --formatted --project *.c

graph:
	@cinclude2dot | xdot -

