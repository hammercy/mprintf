#include "main.h"

/**
 * int _printf - produce output according to a format.
 * @format: pointer to string to be printed
 * @...: variable arguments to be printed.
 *
 * Return: the number of character to be printed.
 */

int _printf(const char *format, ...)
{
	int i = 0, j = 0, k = 0, n = 0, d = 0, ij = 0, ck = 0, l = 0;
	int cnt = 0;
	int numflgs = 10, numcnv = 19;
	char *convspcfr[] = {"s","cdi","bouxX","fFeEgGaA","p"};
	/* s-0,c-1,b-2,f-3,p-4, */
	char *flags = "#+ 0-'*$I";
	char *lengmdfr = "hlLzt";
/* h-1,l-2,L-3,z-4,t-5,hh-6,ll-7*/
	char *charnum = "0123456789";
	char *insrtdataflag = "*$0#*";
	char strbuffer[BUFFERSIZE];
	int convspflag = 1;
	int fwp_num = 1, mult10, temp;
	va_list ap,arg;
	struct dataformat *arrdata[BUFFERSIZE];
	
	va_start(arg, format);
	va_copy(ap, arg);

	while (format[i] != '\0')
	{
		
	  	if (format[i] == '%' && format[i + 1] != '%')
		{
			i = i + 1;
			
			arrdata[j] = (struct dataformat*)malloc(sizeof(struct dataformat));
			if (arrdata[j] != NULL)
			{
				arrdata[j]->ptrdata = NULL;
				arrdata[j]->strdata = NULL;
				arrdata[j]->cnvpsn = 0;
				arrdata[j]->psnflg = 0;
				arrdata[j]->fwidth = 0;
				arrdata[j]->precision = 6;
				arrdata[j]->lengmdfr = 0;
				arrdata[j]->getcnvindex = 7;
				arrdata[j]->tostrindex = 20;
				arrdata[j]->convspcfr = '\0';
				for (k = 0; k < numflgs; k++)
					arrdata[j]->flags[k] = '\0';
			}
			n = 0;
		        while (format[i] != '\0' && arrdata[j] != NULL && convspflag != 0)
			{
				fwp_num = 1;
				mult10 = 1;
				k = 0;
				if (format[i - 1] == '%' && (format[i] > 48 && format[i] < 58))
				{
					
					do {
						temp = ((int)(format[i])) - 48;
						fwp_num = (fwp_num * mult10) + temp;
						mult10 = mult10 * 10;
						i++;
						k++;
					} while (format[i] > 47 && format[i] < 58);
					if (format[i] == '$')
					{
						arrdata[j]->cnvpsn = fwp_num;
						arrdata[j]->psnflg = 1;
					}
					else
					{
						i = i - k;
					}
					
				}
				for (; flags[k] != '\0'; k++)
				{
					if (flags[k] == format[i])
					{
						arrdata[j]->flags[k] = format[i];
						i++;
						k = 0;
					}
				}
				if (format[i] > 48 && format[i] < 58)
				{
					mult10 = 1;
					fwp_num = 1;
					do {
						
						temp = ((int)(charnum[k])) - 48;
						fwp_num = (fwp_num * mult10) + temp;
						mult10 = mult10 * 10;
						i++;
				
					} while (format[i] > 47 && format[i] < 58);
					arrdata[j]->fwidth = fwp_num;			
					
				}
				if (format[i] > 48 && format[i] < 58)
				{
					fwp_num = 1;
					mult10 = 1;
					do {
						temp = ((int)(charnum[k])) - 48;
						fwp_num = (fwp_num * mult10) + temp;
						mult10 = mult10 * 10;
						i++;
					} while (format[i] > 47 && format[i] > 58);
					arrdata[j]->precision = fwp_num;
				}
				n = 0;
				k = 0;
				for (; lengmdfr[k] != '\0'; k++)
				{
					if (format[i] == lengmdfr[k])
					{
						if (n == 0)
							arrdata[j]->lengmdfr = k;
						else
							arrdata[j]->lengmdfr = k + 5;
						n++;
						i++;
						k = 0;
					}
				}
				ck = 0;
				for (l = 0; l < numcnv; )
				{					
					for (k = 0; convspcfr[l][k] != '\0'; k++)
					{
						
						if (format[i] == convspcfr[l][k])
						{
							arrdata[j]->convspcfr = format[i];
							arrdata[j]->getcnvindex = l;
							arrdata[j]->tostrindex = ck;
							convspflag = 0;
							ck = 0;
							for (d = 0; insrtdataflag[d] != '\0'; d++)
							{
								strbuffer[ij] = insrtdataflag[d];
								ij++;
							
							}
							l = numcnv + 10;
							break;
							
						}
						l++;
						ck++;
					} 
				}
			}
			j++;
			convspflag = 1;
		}
		else if (format[i] == '%' && format[i + 1] == '%')
		{
			i++;
			strbuffer[ij] = format[i];
			ij++;
		}
		else
		{
			strbuffer[ij] = format[i];
			ij++;
		}			       
		i++;
	}

	_getdata(arrdata, &ap);	
	cnt = _printstrdata(strbuffer, arrdata);
	return (cnt);
}


