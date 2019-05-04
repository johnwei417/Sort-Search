# Sort-Search
a file **_SongCSV.csv_**, which contains comma separated data on separate lines.  read that file and create a struct for each
song that includes:
* Artist Name
* Song Title
* Album Name
* Duration
* Year of Release
* Hotttnesss
## Basic Algorithm Flow
1. Open the csv file

2. Extract lines, one at a time.

      Put relevant fields (see above) into a struct which is then put into an array of structs. Please note that you are required to allocate memory for structs dynamically.

3. Sort the array of structs by song name. (You may have been doing this in
step 2)

4. Create user interface to search for songs by song name Display relevant
data to user in a neat format Exit only when user enters ZZZ (not 'Quit' or
'q' or 'Q' or 'exit' or 'Exit' or 'EXIT' or 'Leave" or anything other than ZZZ)
