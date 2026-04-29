#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>

//====================================================================================================

// given by the question just fill in these functions and whatnot

int match_space(FILE *f)
{
        // You may insert code here
		//use fgetc here and isspace
		//gotta unget it as well ?? why
		int space; //should be int cause fgetc returns int
		int count;
		
		count = 0;
		
		while(1)
		{
			space = fgetc(f); //save input in char var called space
			if (space == EOF)
				return (count);
			if (isspace(space))
			{
				count++;
			}
			else
			{
				ungetc(space, f); //un-read it? bro why
				return (count);
			}
		}
    return (0);
}

int match_char(FILE *f, char c)
{
        // You may insert code here
		//use fgetc here
		int chars;

		chars = fgetc(f);
		if(chars == EOF)
			return (0);
		if(chars == c)
		{
			return (1); //means the char c matches what is being read from the file f
		}
		else
		{
			ungetc(chars, f);
			return (0);
			}
    // return (0);
}

int scan_char(FILE *f, va_list ap)
{
        // You may insert code here
    return (0);
}

int scan_int(FILE *f, va_list ap)
{
        // You may insert code here
    return (0);
}

int scan_string(FILE *f, va_list ap)
{
        // You may insert code here
    return (0);
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	// ...
	// int ret = ft_vfscanf(stdin, format, ap);
	// ...
	// return ret;
}

