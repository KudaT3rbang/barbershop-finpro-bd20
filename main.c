#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct data {
  char transaction_date[100];
  char customer_name[50];
  char service_type[50];
  char service_name[50];
  int service_amount;
  int service_price;
  int service_total_price;
};

struct data_serv {
  char service_type[50];
  char service_name[50];
  int service_price;
};

// ====================== Utils Section ====================== //

// Function untuk membuka file ditambah error handling, jadi tidak perlu menulis
// error handling tiap file. (Tapi tetap harus fclose).
FILE *open_file(const char *filename, const char *mode) {
  FILE *file = fopen(filename, mode);
  if (file == NULL) {
    printf("Error opening file %s!\n", filename);
    exit(EXIT_FAILURE);
  }
  return file;
}

/* Function untuk print data_transaction (dalam bentuk tabel) yang sudah di
 * sorted atau hasil search.*/
void utils_print_data(struct data *data_transaction_parsed, int data_length) {
  printf("Result :  \n");
  printf("| %-12s | %-12s | %-12s | %-12s | %-12s | %-12s | %-12s |\n", "Date",
         "Customer", "Service Type", "Service Name", "Amount", "Price",
         "Total Price");
  for (int i = 0; i < data_length; i++) {
    printf("| %-12s | %-12s | %-12s | %-12s | %-12d | %-12d | %-12d |\n",
           data_transaction_parsed[i].transaction_date,
           data_transaction_parsed[i].customer_name,
           data_transaction_parsed[i].service_type,
           data_transaction_parsed[i].service_name,
           data_transaction_parsed[i].service_amount,
           data_transaction_parsed[i].service_price,
           data_transaction_parsed[i].service_total_price);
  }
}

/* Function untuk read data_transaction kemudian parse dalam struct pointer */
void utils_read_data_transaction(const char *filename,
                                 struct data *data_transaction_parsed,
                                 int *transaction_count) {
  FILE *data_transaction = open_file(filename, "r");

  // Skip header
  fscanf(data_transaction, "%*[^\n]\n");

  *transaction_count = 0;
  do {
    fscanf(data_transaction, "%99[^,],%49[^,],%49[^,],%49[^,],%d,%d,%d\n",
           data_transaction_parsed[*transaction_count].transaction_date,
           data_transaction_parsed[*transaction_count].customer_name,
           data_transaction_parsed[*transaction_count].service_type,
           data_transaction_parsed[*transaction_count].service_name,
           &data_transaction_parsed[*transaction_count].service_amount,
           &data_transaction_parsed[*transaction_count].service_price,
           &data_transaction_parsed[*transaction_count].service_total_price);
    (*transaction_count)++;
  } while (!feof(data_transaction));

  fclose(data_transaction);
}

// Input validation untuk cek ascending or descending order
void utils_input_validation_sort(int *value) {
  printf("Enter 1 For Ascending Order, Enter 0 For Descending Order : ");
  scanf("%d", value);
  while (*value < 0 || *value > 1) {
    printf("Invalid Input!\nEnter 1 For Ascending Order, Enter 0 For "
           "Descending Order: ");
    scanf("%d", value);
  }
}

// Swap Struct Data when sorting
void utils_swap_struct(struct data *a, struct data *b) {
  struct data data_temp = *a;
  *a = *b;
  *b = data_temp;
}

// Function menghitung frekuensi terbanyak
void utils_count_most_frequent(struct data *data_transaction_parsed,
                               int transaction_count) {
  char most_frequent_service[50];
  int max_total_amount = 0, most_frequent_count = 0;

  for (int i = 0; i < transaction_count; i++) {
    int total_amount = 0;

    for (int j = 0; j < transaction_count; j++) {
      if (strcmp(data_transaction_parsed[i].service_name,
                 data_transaction_parsed[j].service_name) == 0) {
        total_amount += data_transaction_parsed[j].service_amount;
      }
    }
    if (total_amount > max_total_amount) {
      max_total_amount = total_amount;
      strcpy(most_frequent_service, data_transaction_parsed[i].service_name);
      most_frequent_count = total_amount;
    }
  }
  printf("The Most Popular Service This Month (Based On Total Amount): %s\n",
         most_frequent_service);
  printf("Total Amount: %d\n", most_frequent_count);
}

/* Utils untuk mengubah format date yang awalnya tidak punya trailing zero
(misal 2003/9/1) menjadi 2003/09/01 */
void utils_format_date(const char *original_date, char *formatted_date) {
  int year, month, day;
  // Ambil string semisal 2003/9/1 lalu dipecah dan dimasukkan kedalam variabel
  sscanf(original_date, "%d/%d/%d", &year, &month, &day);
  /* assign ke variable formatted_date (melalui pointer) yang akan diisi date
  yang sudah diformat (2003/09/01) */
  sprintf(formatted_date, "%d/%02d/%02d", year, month, day);
}

// ====================== End Of Utils Section ====================== //

// ====================== Print Raw Data Section ====================== //

// Print raw data dari database menjadi bentuk tabel
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

// ====================== End Of Print Raw Data Section ======================//

// ====================== Sort Data Section ====================== //

// Sort Data berdasarkan total harga pembelian
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

// Sorting data berdasarkan tanggal
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
        // Ascending Order (Terlama ke Terbaru)
        if (strcmp(format_date1, format_date2) > 0) {
          utils_swap_struct(&data_transaction_parsed[j],
                            &data_transaction_parsed[j + 1]);
        }
      }
    }
  }
  utils_print_data(data_transaction_parsed, transaction_count);
}

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

// ====================== End Of Sort Data Section ====================== //

// ====================== Search Data Section ====================== //

// Search data berdasarkan inputtan bulan dan tahun lalu print ke tabel
void search_data_based_date() {
  int search_year, search_month, transaction_count = 0, data_length = 0;
  struct data data_transaction_parsed[500];
  struct data data_temp[500];
  utils_read_data_transaction("data_transaction.txt", data_transaction_parsed,
                              &transaction_count);
  printf("Insert Year: ");
  scanf("%d", &search_year);
  printf("Insert Month: ");
  scanf("%d", &search_month);
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

// ====================== End Of Search Data Section ====================== //

// ====================== See Our Service Section ====================== //

/* Digunakan untuk membaca file data_service lalu memparse ke dalam bentuk
struct, dibuthkan 3 parameter const char *filename = e.g "data_service.txt"
(untuk mendapatkan data service) struct data_serv *data_service_parsed = e.g
"data_service_parsed(struct pointer)" (Struct target yang akan dimasukin parsed
data, pakai pointer int *service_count = e.g "&service_count" (mendapatkan
length data)*/
void read_data_service(const char *filename,
                       struct data_serv *data_service_parsed,
                       int *service_count) {
  FILE *data_service = open_file(filename, "r");

  // Skip header file
  fscanf(data_service, "%*[^\n]\n");

  *service_count = 0;
  do {
    fscanf(data_service, "%49[^,],%49[^,],%d\n",
           data_service_parsed[*service_count].service_type,
           data_service_parsed[*service_count].service_name,
           &data_service_parsed[*service_count].service_price);
    (*service_count)++;
  } while (!feof(data_service));

  fclose(data_service);
}

// Fungsi untuk print data_service yang sudah di parsed
void print_service_data(struct data_serv data_service_parsed[],
                        int service_count) {
  printf("Service In Our Barbershop: \n");
  printf("| %-20s | %-20s | %-10s |\n", "Service Type", "Service Name",
         "Price");
  for (int i = 0; i < service_count; i++) {
    printf("| %-20s | %-20s | %-10d |\n", data_service_parsed[i].service_type,
           data_service_parsed[i].service_name,
           data_service_parsed[i].service_price);
  }
}

/* cashier_app adalah function aplikasi kasir barbershop, kasir bisa
memasukkan data nama pelanggan beserta servicenya, nanti bila sudah selesai
memasukkan data, data bisa di print menjadi nota dan data transaksi akan
diupload ke data_transaction.txt*/
void cashier_app() {
  int service_count = 0, max_entry = 0, confirm_upload = 0,
      sum_service_amount = 0, sum_service_price = 0,
      sum_service_total_price = 0;
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
      scanf("%d%*c", &confirm_upload);
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

// ====================== End Of See Our Service Section ======================
// //

// ====================== Add Service Section ====================== //
/* add_service_type adalah fungsi untuk menambahkan data service baru, semisal
barbershop mengeluarkan service baru seperti potong rambut kaki, kasir bisa
menambahkan servicenya (beserta menambahkan harga service) melalui fitur
ini.*/
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
// ====================== End Of Add Service Section ====================== //

int main(void) {
  int choice;
  printf("Welcome to Barbershop Management System\nPlease select the option "
         "you want to use\n");
  printf("1. Print Raw Data\n2. Search Data\n3. Sort Data\n4. See Our "
         "Service\n5. Add Service\n6. Cashier App\n7.Add New Service "
         "Type\nYour choice: ");
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
