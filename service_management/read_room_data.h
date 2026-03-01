int readfile_pasteinfo(RoomInfo info[]){
    fstream  files("D:\\CPP\\Hilbert_Hotel\\Hotel_Room.txt"); 
    if (!files) cerr << "Error";
    static Room rooms[5];
    int t_count = 0;
    string line;
    while (getline(files, line) && t_count < 5) {
        stringstream ss(line);

        string type, guest_s, bedcount_s, bedtype, bath, living_s, price_s;

        getline(ss, type, ',');
        getline(ss, guest_s, ',');
        getline(ss, bedcount_s, ',');
        getline(ss, bedtype, ',');
        getline(ss, bath, ',');
        getline(ss, living_s, ',');
        getline(ss, price_s, ',');

        int guest = stoi(guest_s);
        int bedcount = stoi(bedcount_s);
        bool living = (living_s == "Y");
        double price = stod(price_s);

        map<string,int> bed;
        bed[bedtype] = bedcount;

        rooms[t_count].set_data(type, guest, bed, bath, living, price);

        t_count++;
    }

        map<string, Room*> typeMap;
        for(int i = 0; i < t_count; i++){
            typeMap[rooms[i].getType()] = &rooms[i];
        }

        int r_count = 0;
        while (r_count < 20 && getline(files, line)) {
            if(line.empty()) continue;   

            stringstream ss(line);

            string num_s, type, occ_s,num;

            getline(ss, num_s, ',');
            getline(ss, type, ',');
            getline(ss, occ_s, ',');

            
            bool occ = (occ_s == "YES");

            Room* rtype = typeMap[type];
            info[r_count].setRoom(num_s, rtype, occ);
            r_count ++;
            
        }
        files.close();
        return r_count;

}