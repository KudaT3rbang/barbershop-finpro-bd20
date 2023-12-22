# Dokumentasi Barbershop Software
Page ini berisi dokumentasi kode didalam aplikasi Barbershop Final Project LAB Algo BD-20.

Anggota Kelompok :
* Ananda Samudra Maha Putra - 2702260552
* Nathanael Gilberth Tjandra - 2702223286
* Reynard Wistara Huga Wijaya - 2702234024

## Penjelasan Singkat Aplikasi 
Aplikasi kami merupakan aplikasi semacam POS (Point Of Sales) software dalam suatu barbershop. Jadi terdapat fitur semacam fitur kasir yang berguna untuk tempat pembayaran pelanggan ketika membeli sebuah service. Service itu terdiri dari banyak service semisal Haircut, Styling, Tints, dll. Data service tersebut nantinya akan disimpan didalam database service (data_service.txt). Ketika pelanggan membeli sebuah service maka aplikasi akan membuatkan nota dari transaksi tersebut, dan nantinya histori pembelian akan tersimpan dalam database transaksi (data_transaction.txt).

Aplikasi kami juga memiliki fitur untuk menampilkan data transaksi dan juga memiliki fitur untuk sorting dan searching data transaksi. 

## Penjelasan Kode Dalam Aplikasi
Kode dalam program kami dipecah menjadi beberapa bagian untuk memudahkan pembacaan kode. Berikut ini penjelasan untuk tiap bagian tersebut:
### 1. main()
Bagian main menampilkan main menu utama dalam aplikasi kita dapat memilih beberapa fitur yang ingin digunakan.
```C
int main(void) {
  int choice;
  printf("Welcome to Barbershop Management System\nPlease select the option "
         "you want to use\n");
  printf(
      "1. Print Raw Data\n2. Search Data\n3. Sort Data\n4. See Our Service\n5. "
      "Add New Service Type\nYour "
      "choice: ");
  scanf("%d", &choice);
  while (choice == 0 || choice > 5) {
    printf("Invalid input!\nYour choice: ");
    scanf("%d", &choice);
  }
  switch (choice) {
  case 1:
    print_raw_data();
    break;
  case 2:
    search_data();
    break;
  case 3:
    sort_data();
    break;
  case 4:
    cashier_app();
    break;
  case 5:
    add_service_type();
    break;
  default:
    break;
  }
}
```
Fitur yang bisa dipanggil :
* `print_raw_data()` : Function untuk menampilkan data transaksi mentah (tanpa sorting/hasil search).
* `search_data()` : Function untuk mencari data dari data transaksi.
* `sort_data()` : Function untuk mensorting data dari data transaksi.
* `cashier_app()` : Function untuk aplikasi Point Of Sales (POS), jadi kasir barbershop dapat menginput data transaksi pelanggan.
* `add_service_type()` : Function untuk menambahkan data service baru, semisal barbershop memiliki tipe layanan baru, kita dapat menginput data baru tersebut beserta harganya.
### 2. Print Raw Data Section
Kode pada section ini berguna untuk menampilkan data mentah transaksi. User dapat memasukkan banyak data yang ingin ditampilkan, apabila data yang ingin ditampilkan melebihi jumlah data yang ada, maka program akan menampilkan semua data yang ada.
#### Function `void print_raw_data()`
```C
void print_raw_data() {
  struct data data_transaction_parsed[500];
  int data_length = 0, rows_to_print = 0;
  utils_read_data_transaction("data_transaction.txt", data_transaction_parsed,
                              &data_length);
  printf("Number Of Rows To Print : ");
  scanf("%d", &rows_to_print);
  if (rows_to_print < 0) {
    printf("Invalid Row!");
  } else if (rows_to_print > data_length) {
    utils_print_data(data_transaction_parsed,
                     data_length); // Jika row yang ingin di print melebihi
                                   // jumlah data, print semua data
  } else {
    utils_print_data(
        data_transaction_parsed,
        rows_to_print); // Jika row yang di print tidak melebihi jumlah data,
                        // print sampai row yang dimasukkan
  }
}
```
Alur kode :
1. Pertama kita mendeklarasikan 3 variabel terlebih dahulu, yaitu :
   * `struct data data_transaction_parsed[500]` struct ini berfungsi untuk menyimpan data mentah yang ingin ditampilkan. (Max 500 data, bisa di edit).
   * `int data_length = 0` variabel ini berfungsi menghitung seberapa banyak data mentah.
   * `int rows_to_print = 0` variabel ini berfungsi untuk menampung seberapa banyak data mentah yang ingin di print oleh user.
2. Kemudian kita akan membaca data mentah terlebih dahulu kemudian menyimpannya di dalam `struct data data_transaction_parsed[500]`. Kita menggunakan function `  utils_read_data_transaction("data_transaction.txt", data_transaction_parsed,
                              &data_length);`. (Penjelasan function dapat dilihat di bagian utils).
3. Lalu kita menanyakan kepada user, berapa banyak data yang ingin ditampilkan, data inputtan tersebut nantinya akan disimpan ke dalam variabel `int rows_to_print`. Apabila user memasukkan value kurang dari 0, maka terdapat input validation yang menyatakan bahwa input invalid, lalu akan menyuruh user untuk memasukkan data kembali.
4. Apabila user memasukkan input lebih dari jumlah data maka program akan menampilkan semua data, apabila user memasukkan input tidak lebih dari jumlah data maka tampilkan data sesuai dengan banyaknya data yang ingin ditampilkan user.
   
### 3. Sort Data Section
Bagian ini berfungsi untuk mensorting data, terdapat dua pilihan yaitu mensorting data berdasarkan total harga transaksi dan berdasarkan tanggal transaksi.
#### Function `void sort_data()`
Function ini berfungsi untuk menampilkan menu pilihan sorting data. Akan ditampilkan pilihan sorting berdasarkan total harga transaksi dan berdasarkan tanggal transaksi.
```C
void sort_data() {
  int choice;
  printf("Sort Data Based On: \n1. Based On Total Price\n2. Based On "
         "Date\nYour Choice: ");
  scanf("%d", &choice);
  while (choice == 0 || choice > 2) {
    printf("Invalid input!\nYour choice: ");
    scanf("%d", &choice);
  }
  switch (choice) {
  case 1:
    sort_data_based_sum_price();
    break;
  case 2:
    sort_data_based_date();
    break;
  default:
    break;
  }
}
```
Alur kode :
1. Deklarasi `int choice`, variabel ini berfungsi untuk menyimpan pilihan user.
2. User akan disuruh untuk input pilihan mereka, apakah mereka mau menyortir berdasarkan total harga transaksi atau berdasarkan tanggal transaksi.
3. Kalau inputtan tidak valid maka ulangi input.
4. Case 1 akan memanggil `sort_data_based_sum_price()` yang digunakan untuk menyortir berdasarkan total harga transaksi.
5. Sedangakan Case 2 akan memanggil `sort_data_based_date()` yang digunakan untuk menyortir berdasarkan tanggal transaksi.
#### Function `sort_data_based_sum_price()`
Function ini berguna untuk menyortir data mentah berdasarkan total harga transaksi. User dapat menyortir secara ascending (kecil ke besar) dan descending (besar ke kecil). Data yang di sortir akan ditampilkan dalam bentuk tabel.
```C
void sort_data_based_sum_price() {
  int sort_order, transaction_count = 0;
  struct data data_transaction_parsed[500];
  utils_read_data_transaction("data_transaction.txt", data_transaction_parsed,
                              &transaction_count);
  utils_input_validation_sort(&sort_order);
  for (int i = 0; i < transaction_count; i++) {
    for (int j = 0; j < transaction_count - i - 1; j++) {
      if (sort_order == 0) {
        // Descending Order (Besar ke terkecil)
        if (data_transaction_parsed[j].service_total_price <
            data_transaction_parsed[j + 1].service_total_price) {
          utils_swap_struct(&data_transaction_parsed[j],
                            &data_transaction_parsed[j + 1]);
        }
      } else {
        // Ascending Order (Kecil ke terbesar)
        if (data_transaction_parsed[j].service_total_price >
            data_transaction_parsed[j + 1].service_total_price) {
          utils_swap_struct(&data_transaction_parsed[j],
                            &data_transaction_parsed[j + 1]);
        }
      }
    }
  }
  utils_print_data(data_transaction_parsed, transaction_count);
}
```
Alur kode :
1. Pertama kita mendeklarasikan 3 variabel terlebih dahulu, yaitu :
   * `int search order` variabel ini berfungsi untuk menyimpan input user. Apakah user ingin mensorting data secara descending (0) atau ascending.
   * `int transaction_count = 0` variabel ini berfungsi untuk menyimpan panjang data transaksi.
   * `struct data data_transaction_parsed[500]` variabel ini berfungsi untuk menyimpan data transaksi yang di parsed.
2. Program terlebih dahulu membaca data transaksi menggunakan function `utils_read_data_transaction("data_transaction.txt", data_transaction_parsed, &transaction_count);`. Function ini mengambil data transaksi kemudian memparsed data ke dalam `struct data data_transaction_parsed[500]` yang kita deklarasikan tadi. Lalu function ini akan mereturn pula `transaction_count` atau panjang data mentah tersebut. (Lihat utils_read_data_transaction).
3. Lalu program akan menjalankan function `utils_input_validation_sort(&sort_order);`. Function ini berguna untuk input validasi, apakah user ingin mensorting data secara ascending atau descending.
4. Selanjutnya apabila `sort_order == 0` (Descending) maka jalankan Bubble sort.
   ```C
   for (int i = 0; i < transaction_count; i++) {
   for (int j = 0; j < transaction_count - i - 1; j++) {
     if (sort_order == 0) {
       // Descending Order (Besar ke terkecil)
       if (data_transaction_parsed[j].service_total_price <
           data_transaction_parsed[j + 1].service_total_price) {
         utils_swap_struct(&data_transaction_parsed[j],
                           &data_transaction_parsed[j + 1]);
       }
    ```
   Akan dilakukan algoritma bubble sort didalam program. `utils_swap_struct(&data_transaction_parsed[j],
                           &data_transaction_parsed[j + 1]);` Berfungsi untuk menswap struct.
5. Apabila `sort_order == 1` (Ascending) maka lakukan bubble sort tapi secara ascending.
  ```C
  else {
        // Ascending Order (Kecil ke terbesar)
        if (data_transaction_parsed[j].service_total_price >
            data_transaction_parsed[j + 1].service_total_price) {
          utils_swap_struct(&data_transaction_parsed[j],
                            &data_transaction_parsed[j + 1]);
        }
      }
    }
  }
  ```
6. Setelah data berhasil di sorting kita akan menggunakan function `utils_print_data(data_transaction_parsed, transaction_count);` untuk menampilkan data hasil sorting dalam bentuk tabel.
#### Function `sort_data_based_date()`
Kode pada section ini berfungsi untuk mensorting data berdasarkan tanggal. User dapat menyortir secara ascending (kecil ke besar) dan descending (besar ke kecil). Data yang di sortir akan ditampilkan dalam bentuk tabel.
```C
void sort_data_based_date() {
  int sort_order, transaction_count = 0, most_frequent_count = 0;
  char most_frequent_service[50];
  struct data data_transaction_parsed[500];
  utils_read_data_transaction("data_transaction.txt", data_transaction_parsed,
                              &transaction_count);
  utils_input_validation_sort(&sort_order);
  // Menggunakan lexicographic order
  // (https://en.wikipedia.org/wiki/Lexicographic_order)
  for (int i = 0; i < transaction_count; i++) {
    for (int j = 0; j < transaction_count - i - 1; j++) {
      char format_date1[50], format_date2[50];
      // Untuk menggunakan lexicographic order tanggal harus diformat terlebih
      // dahulu menjadi YYYY/MM/DD (bila bulan dan tanggal tidak dua digit,
      // harus ditambahi trailing 0 (misal september (9) harus diubah menjadi
      // (09) atau tanggal 4 harus diubah menjadi 04 ))
      utils_format_date(data_transaction_parsed[j].transaction_date,
                        format_date1);
      utils_format_date(data_transaction_parsed[j + 1].transaction_date,
                        format_date2);

      if (sort_order == 0) {
        // Descending Order (Terbaru ke terlama)
        // Menggunakan strcmp untuk membandingkan ASCII value dari tanggal
        if (strcmp(format_date1, format_date2) < 0) {
          utils_swap_struct(&data_transaction_parsed[j],
                            &data_transaction_parsed[j + 1]);
        }
      } else {
        if (strcmp(format_date1, format_date2) > 0) {
          utils_swap_struct(&data_transaction_parsed[j],
                            &data_transaction_parsed[j + 1]);
        }
      }
    }
  }
  utils_print_data(data_transaction_parsed, transaction_count);
}
```
Alur Kode :
1. Pertama kita mendeklarasikan 5 variabel terlebih dahulu, yaitu :
   * `int search order` variabel ini berfungsi untuk menyimpan input user. Apakah user ingin mensorting data secara descending (0) atau ascending.
   * `int transaction_count = 0` variabel ini berfungsi untuk menyimpan panjang data transaksi.
   * `struct data data_transaction_parsed[500]` variabel ini berfungsi untuk menyimpan data transaksi yang di parsed.
   * `char most_frequent_service[50];` variabel ini berguna untuk menyimpan service yang paling banyak dibeli pada bulan itu.
   * `int most_frequent_count = 0` variabel ini berguna untuk menyimpan frequensi service yang paling banyak dibeli pada bulan itu.
2. Program terlebih dahulu membaca data transaksi menggunakan function `utils_read_data_transaction("data_transaction.txt", data_transaction_parsed, &transaction_count);`. Function ini mengambil data transaksi kemudian memparsed data ke dalam `struct data data_transaction_parsed[500]` yang kita deklarasikan tadi. Lalu function ini akan mereturn pula `transaction_count` atau panjang data mentah tersebut. (Lihat utils_read_data_transaction).
3. Lalu kita akan mensorting menggunakan lexicographic order, jadi data tanggal harus diformat terlebih dahulu dengan format `YYYY-MM-DD` baru bisa diurutkan menggunakan bubble sort. Kita dapat menggunakan function `utils_format_date(data_transaction_parsed[j].transaction_date, format_date1);` untuk menformat data.
```C
for (int i = 0; i < transaction_count; i++) {
  for (int j = 0; j < transaction_count - i - 1; j++) {
    char format_date1[50], format_date2[50];
    // Untuk menggunakan lexicographic order tanggal harus diformat terlebih
    // dahulu menjadi YYYY/MM/DD (bila bulan dan tanggal tidak dua digit,
    // harus ditambahi trailing 0 (misal september (9) harus diubah menjadi
    // (09) atau tanggal 4 harus diubah menjadi 04 ))
    utils_format_date(data_transaction_parsed[j].transaction_date,
                      format_date1);
    utils_format_date(data_transaction_parsed[j + 1].transaction_date,
                      format_date2);

    if (sort_order == 0) {
      // Descending Order (Terbaru ke terlama)
      // Menggunakan strcmp untuk membandingkan ASCII value dari tanggal
      if (strcmp(format_date1, format_date2) < 0) {
        utils_swap_struct(&data_transaction_parsed[j],
                          &data_transaction_parsed[j + 1]);
      }
    } else {
      // Ascending Order (Terlama ke Terbaru)
      if (strcmp(format_date1, format_date2) > 0) {
        utils_swap_struct(&data_transaction_parsed[j],
                          &data_transaction_parsed[j + 1]);
      }
    }
  }
}
```
`char format_data1[50]` dan `char format_data2[50]` merupakan data sementara untuk menyimpan data tanggal dari `data_transaction_parsed[j].transaction_date` dan `data_transaction_parsed[j + 1].transaction_date`. Konsep bubble sort sama saja dengan bubble sort sebelumnya hanya saja sekarang kita membandingkan data menggunakan strcmp. Kita akan membandingkan `format_data1` dengan `format_data2` lalu kita sorting.

4. Setelah data berhasil di sorting kita akan menggunakan function `utils_print_data(data_transaction_parsed, transaction_count);` untuk menampilkan data hasil sorting dalam bentuk tabel.

### 4. Search Data Section
Bagian ini berfungsi untuk mencari data dari data transaksi, terdapat satu pilihan (mungkin bisa dikembangkan) yaitu fungsi untuk mencari data berdasarkan bulan dan tahun.
#### Function `search_data()`
Function ini berfungsi untuk menampilkan menu pilihan sorting data. Akan ditampilkan pilihan sorting berdasarkan tanggal (mungkin bisa dikembangkan).
```C
void search_data() {
  int choice;
  printf("Search Data Based On: \n1. Based On Date\nYour Choice: ");
  scanf("%d", &choice);
  while (choice == 0 || choice > 1) {
    printf("Invalid input!\nYour choice: ");
    scanf("%d", &choice);
  }
  switch (choice) {
  case 1:
    search_data_based_date();
    break;
  default:
    break;
  }
}
```
Alur kode :
1. Deklarasi `int choice`, variabel ini berfungsi untuk menyimpan pilihan user.
2. User akan disuruh untuk input pilihan mereka, apakah mereka mau mencari data berdasarkan tanggal transaksi.
3. Kalau inputtan tidak valid maka ulangi input.
4. Case 1 akan memanggil `search_data_based_date()` yang digunakan untuk mencari data berdasarkan tanggal transaksi.
#### Function `search_data_based_data()`
Function ini berfungsi untuk mencari data menggunakan data bulan dan tahun.
```C
void search_data_based_date() {
  int search_year, search_month;
  printf("Insert Year: ");
  scanf("%d", &search_year);
  printf("Insert Month: ");
  scanf("%d", &search_month);
  struct data data_transaction_parsed[500];
  struct data data_temp[500];
  int transaction_count = 0, data_length = 0;
  utils_read_data_transaction("data_transaction.txt", data_transaction_parsed,
                              &transaction_count);
  for (int i = 0; i < transaction_count; i++) {
    int year, month;
    // Parse string terlebih dahulu menjadi integer agar bisa dibandingkan
    sscanf(data_transaction_parsed[i].transaction_date, "%d/%d", &year, &month);
    if (year == search_year && month == search_month) {
      data_temp[data_length] = data_transaction_parsed[i];
      data_length++;
    }
  }
  if (data_length == 0) {
    printf("No Data Found!");
  } else {
    utils_print_data(data_temp, data_length);
    utils_count_most_frequent(data_transaction_parsed, transaction_count);
  }
}
```
Alur Kode :
1. Pertama kita mendeklarasikan 6 variabel terlebih dahulu :
   * `int search_year` berguna untuk mengambil inputan tahun yang ingin dicari oleh user.
   * `int search_month` berguna untuk mengambil inputan bulan yang ingin dicari oleh user.
   * `int data_length` berguna untuk menyimpan panjang data hasil pencarian data.
   * `struct data data_transaction_parsed[500]` digunakan untuk menyimpan data transaksi yang di parsed.
   * `struct data data_temp[500]` digunakan untuk menyimpan data hasil pencarian data.
2.  Selanjutnya program akan membaca data transaksi menggunakan function `utils_read_data_transaction("data_transaction.txt", data_transaction_parsed, &transaction_count);` yang nantinya data tersebut di parsed ke `data_transaction_parsed`.
 3. Setelah itu program akan menanyakan kepada user untuk memasukkan data bulan dan tahun yang ingin dicari.
```C
printf("Insert Year: ");
scanf("%d", &search_year);
printf("Insert Month: ");
scanf("%d", &search_month);
```
4. Data tersebut kemudian digunakan untuk linear searching data. Apabila ditemukan tanggal yang sama pada data maka, masukkan data tersebut ke `data_temp` array.
```C
for (int i = 0; i < transaction_count; i++) {
  int year, month;
  // Parse string terlebih dahulu menjadi integer agar bisa dibandingkan
  sscanf(data_transaction_parsed[i].transaction_date, "%d/%d", &year, &month);
  if (year == search_year && month == search_month) {
    data_temp[data_length] = data_transaction_parsed[i];
    data_length++;
  }
}
```
5. Setelah selesai melakukan linear search, data hasil searching akan ditampilkan. Apabila tidak ada data yang ditemukan tampilkan "No Data Found!".
```C
if (data_length == 0) {
  printf("No Data Found!");
```
6. Jika ditemukan data hasil search, maka tampilkan data dalam bentuk tabel, dan tampilkan juga frekuensi service yang paling banyak dibeli.
```C
utils_print_data(data_temp, data_length);
utils_count_most_frequent(data_transaction_parsed, transaction_count);
```
### 5. Our Service Section
Bagian ini berfungsi untuk menambahkan data transaksi apabila customer membeli sebuah layanan di barbershop. Data transaksi tersebut akan disimpan ke database transaksi (`data_transaction.txt`).
#### Function `cashier_app()`
Function aplikasi kasir barbershop, kasir bisa memasukkan data nama pelanggan beserta servicenya, nanti bila sudah selesai memasukkan data, data bisa di print menjadi nota dan data transaksi akan diupload ke data_transaction.txt.
```C
int cashier_app() {
  int service_count = 0, max_entry = 0, sum_service_amount = 0, sum_service_price = 0, sum_service_total_price = 0, confirm_upload = 0;
  time_t t = time(NULL);
  struct tm date = *localtime(&t);
  struct data data_temp[10];
  struct data_serv data_service_parsed[500];
  FILE *data = open_file("data_transaction.txt", "a");
  read_data_service("data_service.txt", data_service_parsed, &service_count);
  print_service_data(data_service_parsed, service_count);
  printf("Input customer name: ");
  scanf(" %[^\n]%*c", data_temp[0].customer_name);
  do {
    strcpy(data_temp[max_entry].customer_name, data_temp[0].customer_name);
    printf("Input Service Type: ");
    scanf(" %[^\n]%*c", data_temp[max_entry].service_type);
    printf("Input Service Name: ");
    scanf(" %[^\n]%*c", data_temp[max_entry].service_name);
    printf("Input Service amount: ");
    scanf("%d", &data_temp[max_entry].service_amount);
    int found = 0;
    for (int z = 0; z < service_count; z++) {
      if (strcmp(data_service_parsed[z].service_type,
                 data_temp[max_entry].service_type) == 0 &&
          strcmp(data_service_parsed[z].service_name,
                 data_temp[max_entry].service_name) == 0) {
        data_temp[max_entry].service_price =
            data_service_parsed[z].service_price;
        data_temp[max_entry].service_total_price =
            data_service_parsed[z].service_price *
            data_temp[max_entry].service_amount;
        found = 1;
        break;
      }
    }

    if (!found) {
      printf("Invalid service type or name.\n");
      printf("Do you want to try again? (0/1)");
      scanf("%d%*c",
            &confirm_upload);
      continue;
    }
    printf("Do you want to input more data? (0/1)");
    scanf("%d", &confirm_upload);
    max_entry++;
  } while (confirm_upload != 0 && max_entry < 10);

  printf("| Barbershop Bill\n");
  printf("| Customer Name: %s\n", data_temp[0].customer_name);
  printf("| Service Type    | Service Name    | Service amount           | "
         "Service Price    | Service Total Price\n");

  for (int z = 0; z < max_entry; z++) {
    printf("| %-15s | %-15s | %-24d | %-16d | %-15d\n",
           data_temp[z].service_type, data_temp[z].service_name,
           data_temp[z].service_amount, data_temp[z].service_price,
           data_temp[z].service_total_price);

    sum_service_amount += data_temp[z].service_amount;
    sum_service_price += data_temp[z].service_price;
    sum_service_total_price += data_temp[z].service_total_price;
  }

  printf("| %-15s | %-15s | %-24d | %-16s | %-15d\n", "Total", "",
         sum_service_amount, "", sum_service_total_price);

  printf("Are you sure want to upload the data? 0/1: ");
  scanf("%d", &confirm_upload);

  while (confirm_upload < 0 || confirm_upload > 1) {
    printf("Invalid input!\nAre you sure want to upload the data? 0/1: ");
    scanf("%d", &confirm_upload);
  }

  if (confirm_upload == 0) {
    printf("Upload data cancelled");
  } else {
    for (int a = 0; a < max_entry; a++) {
      fprintf(data, "\n%d/%d/%d,%s,%s,%s,%d,%d,%d", date.tm_year + 1900,
              date.tm_mon + 1, date.tm_mday, data_temp[a].customer_name,
              data_temp[a].service_type, data_temp[a].service_name,
              data_temp[a].service_amount, data_temp[a].service_price,
              data_temp[a].service_total_price);
      // Print data ke data_transaction.txt
      // yyyy/mm/dd,customer_name,service_type,service_name,service_amount,service_price,service_total_price
    }
    fclose(data);
    printf("Data uploaded!");
  }
}
```
Alur Kode :
1. Pertama kita mendeklarasikan 9 variable terlebih dahulu :
   * `int service_count = 0` merupakan variable untuk menyimpan panjang data service.
   * `int max_entry = 0` merupakan variable untuk menghitung entry (jumlah transaksi) yang dimasukkan customer.
   * `int confirm_upload = 0` merupkan untuk konfirmasi ketika mengupload data.
   * `int sum_service_amount = 0` merupakan variable untuk menghitung jumlah service amount.
   * `int sum_service_price = 0` merupakan variable untuk menyimpan harga service.
   * `int sum_service_total_price = 0` merupakan variable untuk menyimpan total harga yang harus dibayar user.
   * `struct tm date` untuk menyimpan tanggal.
   * `struct data data_temp[10]` merupakan variable untuk menyimpan data nota pembelian sementara (Maximal 10 transaksi).
   * `struct data_serv data_service_parsed[500]` merupakan variable untuk menyimpan data service, sehingga dapat menampilkan service yang tersedia.
2. Selanjutnya program akan memanggil function `read_data_service("data_service.txt", data_service_parsed, &service_count);` dan `print_service_data(data_service_parsed, service_count);` kedua function ini berguna untuk mengambil service yang tersedia di barbershop (melalui data_service.txt). Kemudian menampilkannya dalam bentuk tabel sehingga customer dapat memilih service yang ingin mereka ambil.
3. Kemudian user disuruh untuk memasukkan data nama dan service yang dia pilih.
```C
printf("Input customer name: ");
scanf(" %[^\n]%*c", data_temp[0].customer_name);
do {
  strcpy(data_temp[max_entry].customer_name, data_temp[0].customer_name);
  printf("Input Service Type: ");
  scanf(" %[^\n]%*c", data_temp[max_entry].service_type);
  printf("Input Service Name: ");
  scanf(" %[^\n]%*c", data_temp[max_entry].service_name);
  printf("Input Service amount: ");
  scanf("%d", &data_temp[max_entry].service_amount);
```
4. Kemudian program men-cek terlebih dahulu apakah service_name/service_type ada didalam data_service, bila data valid maka masukkan data transaksi kedalam `data_temp`, kalau tidak ada maka input invalid dan data tidak akan dimasukkan kedalam `data_temp`.
```C
for (int z = 0; z < service_count; z++) {
  if (strcmp(data_service_parsed[z].service_type,
             data_temp[max_entry].service_type) == 0 &&
      strcmp(data_service_parsed[z].service_name,
             data_temp[max_entry].service_name) == 0) {
    data_temp[max_entry].service_price =
        data_service_parsed[z].service_price;
    data_temp[max_entry].service_total_price =
        data_service_parsed[z].service_price *
        data_temp[max_entry].service_amount;
    found = 1;
    break;
  }
}

if (!found) {
  printf("Invalid service type or name.\n");
  printf("Do you want to try again? (0/1)");
  scanf("%d%*c", &confirm_upload);
  continue;
}
```
5. Lalu terdapat validasi, apakah user ingin memasukkan transaksi baru lagi. Bila iya lanjutakan menginput data transaksi kembali, bila tidak lanjut.
```C
printf("Do you want to input more data? (0/1)");
scanf("%d", &confirm_upload);
max_entry++;
```
6. Apabila user sudah memasukkan data transaksi lebih dari 10 kali maka mentok alias tidak bisa memasukkan data transaksi lagi.
```C
while (confirm_upload != 0 && max_entry < 10);
```
7. Selanjutnya program akan menampilkan data transaksi yang dibeli oleh customer, dalam bentuk tabel (nota).
```C
rintf("| Barbershop Bill\n");
printf("| Customer Name: %s\n", data_temp[0].customer_name);
printf("| Service Type    | Service Name    | Service amount           | "
       "Service Price    | Service Total Price\n");

for (int z = 0; z < max_entry; z++) {
  printf("| %-15s | %-15s | %-24d | %-16d | %-15d\n",
         data_temp[z].service_type, data_temp[z].service_name,
         data_temp[z].service_amount, data_temp[z].service_price,
         data_temp[z].service_total_price);

  sum_service_amount += data_temp[z].service_amount;
  sum_service_price += data_temp[z].service_price;
  sum_service_total_price += data_temp[z].service_total_price;
}

printf("| %-15s | %-15s | %-24d | %-16s | %-15d\n", "Total", "",
       sum_service_amount, "", sum_service_total_price);
```
8. Lalu customer akan ditanyai apakah sudah ingin menyelesaikan pembelian, bila iya maka data transaksi akan diupload ke database, bila tidak transaksi akan dibatalkan.
```C
printf("Are you sure want to upload the data? 0/1: ");
scanf("%d", &confirm_upload);

while (confirm_upload < 0 || confirm_upload > 1) {
  printf("Invalid input!\nAre you sure want to upload the data? 0/1: ");
  scanf("%d", &confirm_upload);
}

if (confirm_upload == 0) {
  printf("Upload data cancelled");
} else {
  for (int a = 0; a < max_entry; a++) {
    fprintf(data, "\n%d/%d/%d,%s,%s,%s,%d,%d,%d", date.tm_year + 1900,
            date.tm_mon + 1, date.tm_mday, data_temp[a].customer_name,
            data_temp[a].service_type, data_temp[a].service_name,
            data_temp[a].service_amount, data_temp[a].service_price,
            data_temp[a].service_total_price);
    // Print data ke data_transaction.txt
    // yyyy/mm/dd,customer_name,service_type,service_name,service_amount,service_price,service_total_price
  }
  fclose(data);
  printf("Data uploaded!");
}
```
#### Function `read_data_service(const char *filename, struct data_serv *data_service_parsed, int *service_count)`
Function ini berfungsi untuk membaca data_service, kemudian memparsed datanya.

#### Function `print_service_data(struct data_serv data_service_parsed[],int service_count)`
Function ini digunakan untuk menprint tabel data_service
### 6. Add Service Section
#### Function `add_service_type()`
Function ini berfungsi untuk menambahkan service baru, service baru tersebut nantinya akan dimasukkan kedalam database service (data_service.txt).
```C
void add_service_type() {
  FILE *data_service = open_file("data_service.txt", "a");
  char service_type[50];
  char service_name[50];
  int service_price;

  printf("Input Service Type: ");
  scanf(" %[^\n]%*c", service_type);

  printf("Input Service Name: ");
  scanf(" %[^\n]%*c", service_name);

  printf("Input Service Price: ");
  scanf("%d", &service_price);

  fprintf(data_service, "\n%s,%s,%d", service_type, service_name,
          service_price);
  fclose(data_service);
  printf("New Service Added!");
}
```
Alur Kode :
1. Pertama deklarasikan 3 variable terlebih dahulu, yaitu :
   * `char service_type[50]` variable yang berisi service_type yang ingin ditambahkan.
   * `char service_name[50]` variable yang berisi service_name yang ingin ditambahkan.
   * `int service_price` variable yang berisi service_price yang ingin ditambahkan.
2. Program akan membuka file data_service menggunakan function `open_file`.
```C
FILE *data_service = open_file("data_service.txt", "a");
```
3. User akan disuruh memasukkan service baru.
```C
printf("Input Service Type: ");
scanf(" %[^\n]%*c", service_type);

printf("Input Service Name: ");
scanf(" %[^\n]%*c", service_name);

printf("Input Service Price: ");
scanf("%d", &service_price);
```
4. Kemudian data baru tersebut akan disimpan ke data_service.txt
```C
fprintf(data_service, "\n%s,%s,%d", service_type, service_name,
        service_price);
fclose(data_service);
printf("New Service Added!");
```