# RISET OPENCM & RASPI
______________________________________________________
### FILE DESC
______________________________________________________
24/08/2021 | [EEPROM_READ.ino](https://github.com/syakirahmd/Riset-OpenCM-Raspi/tree/main/Belajar%20API/EEPROM_READ) : Untuk membaca semua data data EEPROM dynamixel.\
24/08/2021 | [sync_write1.ino](https://github.com/syakirahmd/Riset-OpenCM-Raspi/tree/main/Belajar%20API/sync_write1) : syncwrite bekerja dengan baik. Speed  bisa bekerja.\
24/08/2021 | [sync_write.ino](https://github.com/syakirahmd/Riset-OpenCM-Raspi/tree/main/Belajar%20API/sync_write)  : Reg Write tdk bekerja dengan baik, di sudut lebih dari 200 untuk goal position tidak sesuai position yang diminta. Speed blm bisa bekerja (lihat file position_mode1.ino).\
14/10/2021 | [dynamixelmaster](https://github.com/ROBOTIS-GIT/Dynamixel2Arduino/blob/master/src/utility/master.h) : API buat A2D


**TODO**: Cari tahu error reg write apakah bug dari code atau ada parameter yg kurang tepat ataupun kurang.


________________________________________________________
### FILE STATUS
________________________________________________________

sync_write1.ino : ✔ sync write\
sync_write.ino  : ❌ (under riset untuk reg write)\
EEPROM_READ.ino : ✔ membaca semua data EEPROM\
position_mode1.ino: ✔ speed seting test

