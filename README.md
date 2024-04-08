./pipex infile.txt "cat" "wc -l" outfile.txt



./pipex infile.txt "grep ocean" "wc -l" outfile.txt

./pipex input.txt "cat" "grep Some" "sort -u" "wc -l" ofile.txt 






./pipex here_doc DELIMITER "grep Some" "sort -u" ofile.txt
\

//new helper functions!

char *ft_strnew(size_t size)
{
    char *str;

    str = (char *)malloc(sizeof(char) * (size + 1));
    if (!str)
        return NULL;
    ft_bzero(str, size + 1);
    return (str);
}

char **ft_lsttoarr(t_list *lst)
{
    int size = ft_lstsize(lst);
    char **arr = malloc((size + 1) * sizeof(char *));
    if (!arr)
        return NULL;

    for (int i = 0; i < size; i++)
    {
        arr[i] = lst->content;
        lst = lst->next;
    }
    arr[size] = NULL;

    return arr;
}
