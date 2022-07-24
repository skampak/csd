/**************************************************//**
 * @file   main.c                                     *
 * @author Foivos S. Zakkak <zakkak@csd.uoc.gr>       *
 *                                                    *
 * @brief Main function for the needs of cs-240a 2014 *
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "myuniverse.h"

#define BUFFER_SIZE 1024  /**< Maximum length of a line in input file */

// Uncomment the following line to enable debugging prints
// or comment to disable it
//#define DEBUG

#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else  /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */

/**
 * @brief The main function
 *
 * @param argc Number of arguments
 * @param argv Argument vector
 *
 * @return 0 on success
 *         1 on failure
 */
 solar_t *star;
 solar_t *head ,*curr,*tail;
int main(int argc, char** argv)
{
	FILE *fin = NULL;
	char buff[BUFFER_SIZE], event;

	/* Check command buff arguments */
	if ( argc != 2 ) {
		fprintf(stderr, "Usage: %s <input_file> \n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Open input file */
	if (( fin = fopen(argv[1], "r") ) == NULL ) {
		fprintf(stderr, "\n Could not open file: %s\n", argv[1]);
		perror("Opening test file\n");
		return EXIT_FAILURE;
	}

	/* Read input file buff-by-buff and handle the events */
	while ( fgets(buff, BUFFER_SIZE, fin) ) {

		DPRINT("Event: %s \n", buff);

		switch(buff[0]) {

		/* Comment */
		case '#':
			break;

		/* Big Bang
		 * B */
		case 'B':
		{
			if ( big_bang() ) {
				DPRINT("B succeeded\n");
			} else {
				fprintf(stderr, "B failed\n");
			}

			break;
		}

		/* Create a new Galaxy
		 * G <gid> */
		case 'G':
		{
			int gid;
			sscanf(buff, "%c %d", &event, &gid);
			assert(gid > 0);
			DPRINT("%c %d\n", event, gid);

			if ( galaxy_creation(gid) ) {
				DPRINT("%c %d succeeded\n", event, gid);
			} else {
				fprintf(stderr, "%c %d failed\n", event, gid);
			}

			break;
		}

		/* Create a new Star
		 * S <sid> <gid> */
		case 'S':
		{
			int sid;
			int gid;
			sscanf(buff, "%c %d %d", &event, &sid, &gid);
			assert(sid > 0);
			assert(gid > 0);
			DPRINT("%c %d %d\n", event, sid, gid);

			if ( star_birth(sid, gid) ) {
				DPRINT("%c %d %d succeeded\n", event, sid, gid);
			} else {
				fprintf(stderr, "%c %d %d failed\n", event, sid, gid);
			}

			break;
		}

		/* Create a new Planet
		 * P <pid> <distance> <sid> */
		case 'P':
		{
			int pid;
			int sid;
			int distance;
			sscanf(buff, "%c %d %d %d", &event, &pid, &distance, &sid);
			assert(pid > 0);
			assert(sid > 0);
			DPRINT("%c %d %d %d\n", event, pid, distance, sid);

			if ( planet_creation(pid, distance, sid) ) {
				DPRINT("%c %d %d %d succeeded\n", event, pid, distance, sid);
			} else {
				fprintf(stderr, "%c %d %d %d failed\n", event, pid, distance, sid);
			}

			break;
		}

		/* Delete a solar system
		 * D <sid> <distance> */
		case 'D':
		{
			int sid;
			int distance;
			sscanf(buff, "%c %d %d", &event, &sid, &distance);
			assert(sid > 0);
			DPRINT("%c %d %d\n", event, sid, distance);

			if ( star_death(sid, distance) ) {
				DPRINT("%c %d %d succeeded\n", event, sid, distance);
			} else {
				fprintf(stderr, "%c %d %d failed\n", event, sid, distance);
			}

			break;
		}

		/* Trigger an orphan planet crash with a planet
		 * O <oid> <pid> */
		case 'O':
		{
			int oid;
			int pid;
			sscanf(buff, "%c %d %d", &event, &oid, &pid);
			assert(oid > 0);
			assert(pid > 0);
			DPRINT("%c %d %d\n", event, oid, pid);

			if ( planet_orphan_crash(oid, pid) ) {
				DPRINT("%c %d %d succeeded\n", event, oid, pid);
			} else {
				fprintf(stderr, "%c %d %d failed\n", event, oid, pid);
			}

			break;
		}

		/* Trigger an orphan planet cluster split
		 * C <cid1> <cid2> <cid3> */
		case 'C':
		{
			int cid[3];
			sscanf(buff, "%c %d %d %d", &event, cid, cid+1, cid+2);
			assert(cid[0] > 0);
			assert(cid[1] > 0);
			assert(cid[2] > 0);
			DPRINT("%c %d %d %d\n", event, cid[0], cid[1], cid[2]);

			if ( orphans_cluster_crash(cid[0], cid[1], cid[2]) ) {
				DPRINT("%c %d %d %d succeeded\n", event, cid[0], cid[1], cid[2]);
			} else {
				fprintf(stderr, "%c %d %d %d failed\n",
				        event, cid[0], cid[1], cid[2]);
			}

			break;
		}

		/* Trigger the merge of two galaxies
		 * M <gid1> <gid2> */
		case 'M':
		{
			int gid1;
			int gid2;
			sscanf(buff, "%c %d %d", &event, &gid1, &gid2);
			assert(gid1 > 0);
			assert(gid2 > 0);
			DPRINT("%c %d %d\n", event, gid1, gid2);

			if ( galaxy_merger(gid1, gid2) ) {
				DPRINT("%c %d %d succeeded\n", event, gid1, gid2);
			} else {
				fprintf(stderr, "%c %d %d failed\n", event, gid1, gid2);
			}

			break;
		}

		/* Lookup a planet
		 * L <pid> */
		case 'L':
		{
			int pid;
			sscanf(buff, "%c %d", &event, &pid);
			assert(pid > 0);
			DPRINT("%c %d\n", event, pid);

			if ( lookup_planet(pid) ) {
				DPRINT("%c %d succeeded\n", event, pid);
			} else {
				fprintf(stderr, "%c %d failed\n", event, pid);
			}

			break;
		}

		/* Find planets in range
		 * F <pid> <distance> */
		case 'F':
		{
			int pid;
			int distance;
			sscanf(buff, "%c %d %d", &event, &pid, &distance);
			assert(pid > 0);
			DPRINT("%c %d %d\n", event, pid, distance);

			if ( find_planets(pid, distance) ) {
				DPRINT("%c %d %d succeeded\n", event, pid, distance);
			} else {
				fprintf(stderr, "%c %d %d failed\n", event, pid, distance);
			}

			break;
		}

		/* Print a solar system
		 * H <sid> */
		case 'H':
		{
			int sid;
			sscanf(buff, "%c %d", &event, &sid);
			assert(sid > 0);
			DPRINT("%c %d\n", event, sid);

			if ( print_solar(sid) ) {
				DPRINT("%c %d succeeded\n", event, sid);
			} else {
				fprintf(stderr, "%c %d failed\n", event, sid);
			}

			break;
		}

		/* Print a orphan planets cluster
		 * I <cid> */
		case 'I':
		{
			int cid;
			sscanf(buff, "%c %d", &event, &cid);
			assert(cid > 0);
			DPRINT("%c %d\n", event, cid);

			if ( print_ocluster(cid) ) {
				DPRINT("%c %d succeeded\n", event, cid);
			} else {
				fprintf(stderr, "%c %d failed\n", event, cid);
			}

			break;
		}

		/* Print a galaxy
		 * J <gid> */
		case 'J':
		{
			int gid;
			sscanf(buff, "%c %d", &event, &gid);
			assert(gid > 0);
			DPRINT("%c %d\n", event, gid);

			if ( print_galaxy(gid) ) {
				DPRINT("%c %d succeeded\n", event, gid);
			} else {
				fprintf(stderr, "%c %d failed\n", event, gid);
			}

			break;
		}

		/* Print universe
		 * U */
		case 'U':
		{
			if ( print_universe() ) {
				DPRINT("U succeeded\n");
			} else {
				fprintf(stderr, "U failed\n");
			}

			break;
		}

		/* End of the World (Optional)
		 * E */
		case 'E':
		{
			if ( end_of_the_world() ) {
				DPRINT("E succeeded\n");
			} else {
				fprintf(stderr, "E failed\n");
			}

			break;
		}

		/* Empty line */
		case '\n':
			break;

		/* Ignore everything else */
		default:
			DPRINT("Ignoring buff: %s \n", buff);

			break;
		}
	}

	return (EXIT_SUCCESS);
}
