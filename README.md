# 🚗 Sistem Pengingat Pemeliharaan Kendaraan Berbasis IoT

Proyek IoT menggunakan **ESP32**, **Blynk**, dan **OLED Display** untuk memberikan pengingat pemeliharaan kendaraan berdasarkan:

* 📍 Jarak tempuh (KM)
* ⏱️ Waktu penggunaan

Sistem akan memberikan notifikasi ketika kendaraan sudah waktunya melakukan servis.

---

# ✨ Fitur

* Monitoring total kilometer kendaraan
* Pengingat servis berdasarkan KM
* Pengingat servis berdasarkan waktu
* Tampilan realtime pada OLED
* Monitoring melalui aplikasi Blynk
* Notifikasi otomatis ke smartphone
* Simulasi menggunakan Wokwi

---

# 🛠️ Komponen

| Komponen           | Jumlah     |
| ------------------ | ---------- |
| ESP32 DevKit       | 1          |
| OLED SSD1306 I2C   | 1          |
| Push Button        | 2          |
| Kabel Jumper       | Secukupnya |
| Smartphone + Blynk | 1          |

---

# 🔌 Wiring

## OLED I2C

| OLED | ESP32  |
| ---- | ------ |
| VCC  | 3.3V   |
| GND  | GND    |
| SDA  | GPIO21 |
| SCL  | GPIO22 |

---

## Tombol Tambah KM

| Push Button    | ESP32  |
| -------------- | ------ |
| Satu sisi      | GPIO18 |
| Satu sisi lain | GND    |

---

## Tombol Reset Service

| Push Button    | ESP32  |
| -------------- | ------ |
| Satu sisi      | GPIO19 |
| Satu sisi lain | GND    |

Menggunakan:

```cpp
INPUT_PULLUP
```

---

# 📱 Setup Blynk

## 1. Buat Template

Pada Blynk Cloud:

* Hardware: ESP32
* Connection Type: WiFi

---

## 2. Buat Datastream

| Nama     | Virtual Pin |
| -------- | ----------- |
| Total KM | V0          |
| Status   | V1          |

---

## 3. Buat Event

Nama event:

```text
service_alert
```

Aktifkan:

* Push Notification

---

# 💻 Library yang Digunakan

Install library berikut pada Arduino IDE:

* Blynk
* Adafruit SSD1306
* Adafruit GFX

---

# 🚀 Cara Menjalankan

## 1. Clone Repository

```bash
git clone https://github.com/username/repository-name.git
```

---

## 2. Buka di Wokwi / Arduino IDE

Upload file:

* `diagram.json`
* `sketch.ino`

---

## 3. Masukkan Data Blynk


```cpp
#define BLYNK_TEMPLATE_ID "TMPL6C-2834LN"
#define BLYNK_TEMPLATE_NAME "Reminder Service"
#define BLYNK_AUTH_TOKEN "oEbkszrv3iLB7RXVQPbX1LhjlUS2fsdX"
```

---

## 4. Jalankan Simulasi

Pada Wokwi:

* Klik **Start Simulation**

---

# 🎮 Cara Penggunaan

## Tombol GPIO18

Menambah kilometer kendaraan.

```text
1 klik = +500 KM
```

---

## Tombol GPIO19

Reset jadwal servis setelah kendaraan selesai diservis.

---

# 📊 Cara Kerja Sistem

1. ESP32 membaca input tombol
2. Total KM kendaraan bertambah
3. Sistem mengecek:

   * KM servis
   * waktu servis
4. Jika melebihi batas:

   * OLED menampilkan peringatan
   * Blynk mengirim notifikasi
5. Data tampil realtime pada dashboard

---

# 📷 Dashboard Blynk

Widget yang digunakan:

| Widget       | Fungsi               |
| ------------ | -------------------- |
| Gauge        | Menampilkan Total KM |
| Label        | Status kendaraan     |
| Notification | Pengingat servis     |

---

# 🌐 Platform

* ESP32
* Blynk IoT
* Wokwi Simulator
* Arduino IDE

---

# 📌 Pengembangan Selanjutnya

* Sensor kecepatan roda asli
* Penyimpanan EEPROM
* GPS Tracking
* Riwayat servis kendaraan
* Firebase Database
* Monitoring oli dan aki
* Telegram Notification

---

# 👨‍💻 Author

* Ichsan Pratama Putra
* 23552011205

---

# 📄 License

Project ini dibuat untuk pembelajaran dan pengembangan sistem IoT kendaraan.
