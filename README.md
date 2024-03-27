./pipex infile.txt "cat" "wc -l" outfile.txt



./pipex infile.txt "grep ocean" "wc -l" outfile.txt

./pipex input.txt "cat" "grep Some" "sort -u" "wc -l" ofile.txt 






./pipex here_doc DELIMITER "grep Some" "sort -u" ofile.txt
