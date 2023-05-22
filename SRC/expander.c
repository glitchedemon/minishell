#include "minishell.h"

char *ft_expjoin(char *var, char *envar, char *usrvar)
{
	char *str;
	int i;
	int size;
	int j;
	int k;

	k = 0;
	size = ft_strlen(envar) + (ft_strlen(var) - ft_strlen(usrvar));
	str = malloc(sizeof(char) * size);
	i = 0;
	j = 0;
	while(i < size)
	{
		if(var[j] == '$')
		{
			while(envar[k])
				str[i++] = envar[k++];
			j += ft_strlen(usrvar) + 1;
		}
		str[i] = var[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return(str);
}

char *ft_expandvar(char *var)
{
    int i;
    char *usrvar;
    char *envar;
    int k;
	int start;

    k = 0;
    i = 0;
	start = 0;
	if(var[i] == '$')
	{
		i++;
		start = i;
	}
	else
	{
		while(var[i] != '$')
			i++;
		start = i + 1;
		i++;
	}
    while(var[i] != '\0')
	{
		if(var[i] == ' ' || var[i] == '\''
		|| var[i] == '\"')
			break;
		i++;
        k++;
	}
    usrvar = ft_calloc(sizeof(char), k + 1);
	i = 0;
	while(k > 0)
	{
		usrvar[i++] = var[start++]; 
		k--;
	}
	usrvar[i] = '\0';
    envar = getenv(usrvar);
	return(ft_expjoin(var, envar, usrvar));
}

char	*ft_getpath(char *tilde)
{
	int i;
	char *path;
	char *tmp;
	int start;
	int k;

	k = 0;
	path = getenv("HOME");
	if(tilde[0] != '~')
		return(tilde);
	i = 1;
	start = i;
	while(tilde[i] != ' ' && tilde[i] != '\0')
	{
		i++;
		k++;
	}
	i=0;
	tmp = ft_calloc(sizeof(char), k + 1);
	while(k > 0)
	{
		tmp[i++] = tilde[start++];
		k--;
	}
	path = ft_strjoin(path, tmp);
	return path;
}

char **ft_expander(char **prompt)
{
	int i;

	i = 0;
    while(prompt[i] != NULL)
    {
        if(ft_strchr(prompt[i], '$'))
            prompt[i] = ft_expandvar(prompt[i]);
		else if(ft_strchr(prompt[i], '~'))
			prompt[i] = ft_getpath(prompt[i]);
        i++;
    }
    return prompt;
}