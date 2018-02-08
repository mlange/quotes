#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void sPrintByte(char ptr)
{
    unsigned char ii,
                  bitset,
                  bitmask;

    char result[36] = "";

    /* Set the high-order bit of the bitmask. */
    bitmask = 1 << 7;

    /* Give ourselves a nicer alias to work with. */
    bitset = ptr;

    /* Cycle through every bit in the bitset. */
    for (ii=1; ii <= 8; ii++)
    {
        /* Get the value of this bit. */
        char *bit = ((bitset & bitmask) == 0) ? "0" : "1";

        /* Add this bit's value to our result. */
        strcat(result, bit);

        /* Put a spacer in after every eight bit. */
        if ((ii % 8 == 0) && (ii != 32))
            strcat(result, " ");

        /* Shift the bitset one left. */
        bitset <<= 1;
    }

    printf("%s ", result);
}

void misEncryptRPBF(char *string, long inlength, long *outlength)
{
    long ii;

    unsigned char bitmask,
		  *ptr;

    *outlength = inlength;

    printf("   BIT MASK  ");
    
    for (ii = 0, ptr = (unsigned char *) string; ii < inlength; ii++, ptr++)
    {
	bitmask = (unsigned char) (ii % 255) + 1;

	if (ii < 5) sPrintByte(bitmask);

        if (bitmask & *ptr)
            *ptr ^= bitmask;
        else
            *ptr |= bitmask;
    }

    printf("\n");

    return;
}

void misDecryptRPBF(char *string, long inlength, long *outlength)
{
    long ii;

    unsigned char bitmask,
		  *ptr;

    *outlength = inlength;

    printf("   BIT MASK  ");

    for (ii = 0, ptr = (unsigned char *) string; ii < inlength; ii++, ptr++)
    {
	bitmask = (unsigned char) (ii % 255) + 1;

	if (ii < 5) sPrintByte(bitmask);

        if (bitmask & *ptr)
            *ptr ^= bitmask;
        else
            *ptr |= bitmask;
    }

    printf("\n");

    return;
}

void main(int argc, char *argv[])
{
    long ii,
         inlength, 
         outlength;

    char data[10];

    char *ptr;

    FILE *infile;

    infile = fopen("infile", "rb");

    fread(data, 1, sizeof(data), infile);

    printf(" CLEAR TEXT  ");
    for (ii = 0, ptr = data; ii < 5; ii++, ptr++)
    {
        sPrintByte(*ptr);
    }
    printf("\n\n");

    misEncryptRPBF(data, sizeof(data), &outlength);
    printf("CIPHER TEXT  ");
    for (ii = 0, ptr = data; ii < 5; ii++, ptr++)
    {
        sPrintByte(*ptr);
    }
    printf("\n\n");

    misDecryptRPBF(data, outlength, &inlength);
    printf(" CLEAR TEXT  ");
    for (ii = 0, ptr = data; ii < 5; ii++, ptr++)
    {
        sPrintByte(*ptr);
    }
    printf("\n\n");

    fclose(infile);

    exit(0);
}
