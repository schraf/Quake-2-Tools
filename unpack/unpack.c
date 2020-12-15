/*
===========================================================================
Copyright (C) 1997-2006 Id Software, Inc.

This file is part of Quake 2 Tools source code.

Quake 2 Tools source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake 2 Tools source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Quake 2 Tools source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/

/*
 * Unpack -- a completely non-object oriented utility...
 * This is a port of the original unpack tool written in Java
 */

#include "cmdlib.h"
#include "qfiles.h"

qboolean PatternMatch (const char* pattern, const char* s)
{
	const char		*pos;
	int				index;
	int				remaining;
	int				patlen;
	int				slen;

	if (!strcmp(pattern, s))
		return true;

	// fairly lame single wildcard matching
	pos = strchr(pattern, '*');

	if (pos == NULL)
		return false;

	index = (intptr_t)(pos - pattern);

	if (Q_strncasecmp(pattern, s, index))
		return false;

	patlen = (int)strlen(pattern);
	slen = (int)strlen(s);
	index += 1;	// skip the *
	remaining = patlen - index;

	if (slen < remaining)
		return false;

	if (Q_strncasecmp(pattern + index, s + slen - remaining, remaining))
		return false;

	return true;
}

void Usage ()
{
	printf ("Usage: unpack <packfile> <match> <basedir>\n");
	printf ("   or: unpack -list <packfile>\n");
	printf ("<match> may contain a single * wildcard\n");
	exit (1);
}

void CreatePathFromFilename (const char* filename)
{
	char	path[1024];

	ExtractFilePath (filename, path);
	CreatePath (path);
}

int main (int argc, char **argv)
{
	int				i;
	int				numLumps;
	char			*pakName;
	char			*pattern;
	FILE			*pakfile;
	dpackheader_t	header;
	int				dirpos;
	dpackfile_t		dirfile;
	char			*buffer;
	int				bufsize;
	char			path[1024];
	char			*outbase;

	printf ("---- unpack ----\n");

	if (argc == 3) {
		if (strcmp(argv[1],"-list") != 0)
		{
			Usage ();
			return;
		}

		pakName = argv[2];
		pattern = NULL;
		outbase = NULL;
	} else if (argc == 4) {
		pakName = argv[1];
		pattern = argv[2];
		outbase = argv[3];
	} else {
		Usage ();
		return;
	}

	pakfile = SafeOpenRead (pakName);
	SafeRead (pakfile, &header, 12);

	// read the header
	header.ident = LittleLong(header.ident);
	header.dirofs = LittleLong(header.dirofs);
	header.dirlen = LittleLong(header.dirlen);

	if (header.ident != IDPAKHEADER)
		Error ("%s is not a pakfile.", pakName);

	// read the directory
	dirpos = header.dirofs;
	numLumps = header.dirlen / 64;
	buffer = NULL;
	bufsize = 0;

	fseek (pakfile, dirpos, SEEK_SET);
	printf ("%d lumps in %s\n", numLumps, pakName);

	for (i = 0 ; i < numLumps ; i++)
	{
		fseek (pakfile, dirpos, SEEK_SET);
		SafeRead (pakfile, &dirfile, 64);
		dirpos += 64;

		dirfile.filepos = LittleLong(dirfile.filepos);
		dirfile.filelen = LittleLong(dirfile.filelen);

		if (pattern == NULL)
		{
			// listing mode
			printf ("%s : %d bytes\n", dirfile.name, dirfile.filelen);
		}
		else if (PatternMatch (pattern, dirfile.name))
		{
			FILE* outfile;

			if (buffer == NULL)
			{
				buffer = malloc(dirfile.filelen);
				bufsize = dirfile.filelen;
			}
			else if (bufsize < dirfile.filelen)
			{
				buffer = realloc(buffer, dirfile.filelen);
				bufsize = dirfile.filelen;
			}

			printf ("Unpaking %s %d bytes\n", dirfile.name, dirfile.filelen);

			// load the lump
			fseek (pakfile, dirfile.filepos, SEEK_SET);
			SafeRead (pakfile, buffer, dirfile.filelen);

			sprintf (path, "%s/%s", outbase, dirfile.name);
			CreatePathFromFilename (path);
			outfile = SafeOpenWrite(path);
			SafeWrite(outfile, buffer, dirfile.filelen);
			fclose(outfile);
		}
	}

	if (buffer != NULL)
		free(buffer);

	fclose(pakfile);
	return 0;
}
