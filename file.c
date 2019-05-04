#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 4096
struct song {
    //int song_id;
    char *song_title;
    char *album_name;
    char *artist_name;
    double duration;
    int release_year;
    double hotness;
};

int binary_search(struct song *songs, int l, int r, char *songName){

    if (r >= l) { 
        int mid = l + (r - l) / 2; 
  
        // If the element is present at the middle 
        // itself 
        if (strcmp(songs[mid].song_title, songName) == 0) 
            return mid; 
  
        // If element is smaller than mid, then 
        // it can only be present in left subarray 
        if (strcmp(songs[mid].song_title, songName) > 0) 
            return binary_search(songs, l, mid - 1, songName); 
  
        // Else the element can only be present 
        // in right subarray 
         if (strcmp(songs[mid].song_title, songName) < 0) 
        return binary_search(songs, mid + 1, r, songName); 
    } 
  
    // We reach here when element is not 
    // present in array 
    return -1; 
}




int compar(const void *p, const void *q) {
    //return (*(struct song *)p).song_id - (*(struct song *)q).song_id;
    return strcmp((*(struct song *)p).song_title , (*(struct song *)q).song_title);
}

int main(int argc, char **argv) {
    int fd; // file descriptor
    int num; // actual number read from file each time
    char line[BUFSIZE]; // used to temporarily store the record
    char buff[BUFSIZE]; // each time read BUFSIZE bytes
    int j;
    j = 0;

    char* songName =  malloc(sizeof *songName);
    int found;

    fd = open("SongCSV.csv", O_RDONLY); // open the file for read-only
    
    struct song *songs;
    songs = malloc(sizeof(struct song));

    /* error check */
    if (fd < 0) {
        perror(argv[0]);
        exit(errno);
    }
    
    /* read one byte at a time */
   
    printf("After Sorting by Song Name:\n");
    int i = 0;
    int offset = 0;
    while ((num = read(fd, buff, BUFSIZE)) > 0) { // there are still bytes 
         // locate the newline character in buff
        while (buff[i] != '\n') {
            line[i] = buff[i];
            i++;
            offset++;
        }
       
        
        // reposition to the start of next line with the help of offset
        // the offset is going to be the bytes of lines that I have already processed
      
                if (j != 0) {
                    songs = realloc(songs, sizeof(struct song) * (j+1));
                }
                
                char *token;
                int k;
                for (k = 0, token = strtok(line, ","); token != NULL; token = strtok(NULL, ","), k++) {
                    // printf("%s\n", token);
                    //if (k == 0) { // song number
                    //    songs[j].song_id = atoi(token);
                    //}

                     if (k == 8) { // artist name
                        // allocate memory
                        songs[j].artist_name = malloc(sizeof(char) * (strlen(token) + 1));
                        strcpy(songs[j].artist_name, token);
                    }

                    if (k == 3) { // album name
                        // allocate memory
                        songs[j].album_name = malloc(sizeof(char) * (strlen(token) + 1));
                        strcpy(songs[j].album_name, token);
                    }

                     if (k == 17) { // song title
                        // allocate memory
                        songs[j].song_title = malloc(sizeof(char) * (strlen(token) + 1));

                        char *p = token;
                        p++; 
                        p[strlen(p)-1] = 0;

                        strcpy(songs[j].song_title, p);
                    }

                    if (k == 10) { // duration
                        songs[j].duration= atof(token);
                    }
                    
                    if (k == 18) { // release year;
                        songs[j].release_year = atoi(token);
                    }

                    if (k == 14) { // hotness
                        songs[j].hotness = atof(token);
                    }
                } 
                // make sure the information is stored correctly
              // printf("%d %s\n", songs[j].song_id, songs[j].album_name);
            
            j++;
            offset++; // for the newline character
            i = 0; // reset index 
            memset(buff, '\0', BUFSIZE); // reset buff
            memset(line, '\0', BUFSIZE); // reset line 
            lseek(fd, offset, SEEK_SET);
    }
    //sorting the struct
    qsort(songs, j, sizeof(struct song), compar);    
     
     /**
      * this part for testing
      int x;
     for ( x = 0; x < j; x++){
        printf("%s     %f\n", songs[x].song_title, songs[x].hotness);
    }
**/
    

 
     printf("*****************USER INTERFACE**********************\n");

     do{
          printf("********************************************\n");
    
           scanf ("%[^\n]\n", songName);
           //try to search the input from the structure songs;
        found = binary_search(songs,0,j-1,songName);
        if((songName != NULL) && (strcmp(songName,"ZZZ")!=0)){
           //printf("Found at index of %d in ordered songs structure\n", found);
           printf("Song Title: %s \nArtist Name: %s | Album Name: %s |\nDuration: %f | Year of Release: %d | Hotttnesss: %f\n", 
           songs[found].song_title, songs[found].artist_name,
           songs[found].album_name, songs[found].duration, songs[found].release_year, songs[found].hotness           
           );
        }
        printf("\n");
     
     }while(strcmp(songName,"ZZZ")!=0);
         
         printf("Exiting....\n");
         printf("DONE! THANK YOU SO MUCH\n");
   
    if (num < 0) {
        perror(argv[0]);
        exit(errno);
    }

    return 0;
}
