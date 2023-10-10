#include "shell.h"

// FUNCTIONS TO CREATE
// strchr()
// strncmp()

int _unsetenv(const char *name)
{

}

int _setenv(const char *name, const char *value, int overwrite)
{
    int i, checkName, num_vars = 0;
    char **new_env;

    if (!name || _strchr(name, '='))
        return (-1);
    for (i = 0; environ[i]; i++)
    {
        checkName = strncmp(environ[i], name, _strlen(name));
        if (checkName == 0 && environ[i][_strlen(name)] == '=')
        {
            if (!overwrite)
                return (0);
            free(environ[i]);
            environ[i] = (char *)malloc(_strlen(name) + _strlen(value) + 2);
            if (!environ[i])
                return (-1);
            sprintf(environ[i], "%s=%s", name, value);
            return (0);
        }
    }
    while (environ[num_vars])
        num_vars++;
    new_env = (char **)malloc((num_vars + 2) * sizeof(char *));
    if (!new_env)
        return (-1);
    for (int i = 0; i < num_vars; i++)
        new_env[i] = environ[i];
    new_env[num_vars] = (char *)malloc(_strlen(name) + _strlen(value) + 2);
    if (!new_env[num_vars])
        return (-1);
    sprintf(new_env[num_vars], "%s=%s", name, value);
    new_env[num_vars + 1] = NULL;

    environ = new_env;
    return (0);
}
