<div align="center">

# 🚰 Sistem Pemantauan Volume Air Berbasis IoT dengan Triple Modular Redundancy (TMR)

### Proyek Akhir Mata Kuliah Fault Tolerant System

Implementasi **Triple Modular Redundancy (TMR)** menggunakan mikrokontroler ESP32 dan tiga sensor ultrasonik HC-SR04 untuk meningkatkan keandalan sistem pemantauan volume air secara real-time.

</div>

---

# 📖 Deskripsi Proyek

Sistem pemantauan volume air pada tandon umumnya menggunakan satu sensor sebagai sumber data utama. Pendekatan tersebut memiliki kelemahan berupa **Single Point of Failure (SPOF)**, yaitu kondisi ketika kegagalan satu sensor menyebabkan seluruh sistem tidak dapat memberikan informasi yang akurat.

Pada proyek ini dikembangkan sebuah sistem **Fault Tolerant Water Level Monitoring** yang menerapkan konsep **Triple Modular Redundancy (TMR)** menggunakan tiga sensor ultrasonik HC-SR04 yang dikendalikan oleh ESP32. Sistem dirancang agar tetap dapat beroperasi meskipun salah satu sensor mengalami gangguan sementara (*transient fault*) maupun kerusakan permanen (*permanent fault*).

Untuk meningkatkan keandalan sistem, diterapkan beberapa mekanisme fault tolerance, antara lain:

* **Sequential Triggering** untuk menghindari crosstalk antar sensor.
* **Median-Based Fault Detection** untuk mendeteksi sensor yang mengalami anomali.
* **Majority Voting** untuk menentukan nilai keluaran yang paling representatif.
* **Fault Masking** untuk mengabaikan sensor yang mengalami kegagalan.
* **Graceful Degradation** agar sistem tetap berjalan dengan dua sensor aktif.
* **Fail-Safe Mode** ketika jumlah sensor aktif tidak lagi memenuhi syarat operasional.

---

# 🎯 Tujuan Proyek

1. Mengimplementasikan konsep Triple Modular Redundancy (TMR) pada sistem pemantauan volume air.
2. Mengurangi dampak kegagalan sensor tunggal terhadap keluaran sistem.
3. Meningkatkan reliability dan dependability sistem monitoring.
4. Menguji kemampuan sistem dalam menangani gangguan sementara maupun permanen.
5. Menerapkan konsep Fault Tolerant System pada perangkat IoT berbasis ESP32.

---

# 🏗️ Arsitektur Sistem

```text
                HC-SR04 #1
                     │
                     │
                HC-SR04 #2
                     │
                     │
                HC-SR04 #3
                     │
                     ▼

        ┌────────────────────────┐
        │         ESP32          │
        │                        │
        │ Sequential Triggering  │
        │ Fault Detection        │
        │ Majority Voting        │
        │ Fault Masking          │
        └───────────┬────────────┘
                    │
                    ▼

          Dashboard Monitoring
                Real-Time
```

Pada sistem ini ESP32 berfungsi sebagai:

* Pengendali pembacaan sensor secara bergantian.
* Unit pemrosesan data.
* Voter digital pada arsitektur TMR.
* Server web untuk dashboard monitoring.

---

# ✨ Fitur Utama

## 🔄 Triple Modular Redundancy (TMR)

Sistem menggunakan tiga sensor HC-SR04 yang mengukur objek yang sama secara paralel.

Keuntungan:

* Menghilangkan Single Point of Failure.
* Meningkatkan reliabilitas sistem.
* Mendukung fault masking.

---

## 📡 Sequential Triggering

Karena ketiga sensor dipasang berdekatan, terdapat potensi interferensi gelombang ultrasonik (*crosstalk*).

Untuk mengatasinya, sensor dipicu secara bergantian:

```text
Sensor 1 → Delay → Sensor 2 → Delay → Sensor 3
```

Manfaat:

* Mengurangi interferensi antar sensor.
* Meningkatkan stabilitas pembacaan.
* Menjaga akurasi hasil pengukuran.

---

## 🛡 Fault Detection

Sistem menghitung nilai median dari tiga pembacaan sensor.

Jika terdapat sensor dengan deviasi yang melebihi ambang batas:

```text
|Nilai Sensor - Median| > Threshold
```

maka sensor tersebut akan ditandai sebagai fault.

Nilai threshold yang digunakan:

```cpp
#define THRESHOLD 5.0
```

---

## 🗳 Majority Voting

Jika seluruh sensor sehat:

```text
Output = Rata-rata Sensor 1, Sensor 2, dan Sensor 3
```

Jika satu sensor mengalami fault:

```text
Sensor 1 = 20 cm
Sensor 2 = 21 cm
Sensor 3 = 85 cm (Fault)

Output = Rata-rata Sensor 1 dan Sensor 2
```

Sensor yang mengalami fault tidak akan digunakan dalam proses voting.

---

## 🔧 Graceful Degradation

Sistem tetap dapat beroperasi secara normal apabila:

* 3 dari 3 sensor aktif
* 2 dari 3 sensor aktif

Walaupun performa mengalami degradasi, sistem masih mampu memberikan hasil yang valid.

---

## 🚨 Fail-Safe Mode

Apabila jumlah sensor aktif kurang dari dua:

```text
Active Sensors < 2
```

maka sistem masuk ke mode:

```text
HALTED
```

untuk mencegah pengambilan keputusan yang tidak valid.

---

# 🌐 Dashboard Monitoring

Dashboard berbasis web digunakan untuk menampilkan kondisi sistem secara real-time.

Informasi yang ditampilkan meliputi:

### Data Sensor

* Sensor 1 Distance
* Sensor 2 Distance
* Sensor 3 Distance

### Hasil Voting

* Median Value
* TMR Final Output

### Status Sistem

* Sistem Normal (3/3 Aktif)
* Degradasi (2/3 Aktif)
* Fail-Safe (HALTED)

### Monitoring Fault

* Sensor Sehat
* Transient Fault
* Permanent Fault

### Fault History

Riwayat fault yang pernah terjadi pada sistem.

---

# 🛠 Kebutuhan Perangkat Keras

| Komponen               | Jumlah     |
| ---------------------- | ---------- |
| ESP32                  | 1          |
| HC-SR04                | 3          |
| Breadboard             | 1          |
| Kabel Jumper           | Secukupnya |
| Tandon Air / Prototype | 1          |

---

# 🔌 Konfigurasi Pin

| Sensor   | Trigger | Echo    |
| -------- | ------- | ------- |
| Sensor 1 | GPIO 5  | GPIO 18 |
| Sensor 2 | GPIO 19 | GPIO 21 |
| Sensor 3 | GPIO 22 | GPIO 23 |

---

# 📂 Struktur Repository

```text
.
├── TMRHCSR04.ino
├── index.html
├── assets/
│   ├── dashboard.png
│   ├── wiring-diagram.png
│   └── architecture.png
└── README.md
```

---

# 🚀 Panduan Instalasi

## 1. Clone Repository

```bash
git clone https://github.com/username/nama-repository.git
```

---

## 2. Instal Arduino IDE

Unduh dan instal Arduino IDE:

https://www.arduino.cc/en/software

---

## 3. Instal Board ESP32

Masuk ke:

```text
Tools
→ Board Manager
→ Cari "ESP32"
→ Install
```

---

## 4. Konfigurasi WiFi

Buka file program ESP32 dan sesuaikan bagian berikut:

```cpp
const char* ssid = "NAMA_WIFI";
const char* password = "PASSWORD_WIFI";
```

---

## 5. Upload Program ke ESP32

Pilih:

```text
Board : ESP32 Dev Module
Port  : COM sesuai perangkat
```

Kemudian upload file:

```text
TMRHCSR04.ino
```

---

## 6. Jalankan Sistem

Setelah ESP32 berhasil terhubung ke WiFi, buka Serial Monitor.

Contoh keluaran:

```text
Connected to WiFi
IP Address:
192.168.1.100
```

Buka browser dan akses:

```text
http://192.168.1.100
```

Dashboard monitoring akan tampil secara otomatis.

---

# 🧪 Pengujian Sistem

## Pengujian 1 — Kondisi Normal

Semua sensor aktif.

Hasil yang diharapkan:

```text
3/3 Sensor Aktif
Status: NORMAL
```

---

## Pengujian 2 — Permanent Fault

Lepaskan kabel Echo salah satu sensor.

Hasil yang diharapkan:

```text
2/3 Sensor Aktif
Fault Masking Aktif
Sistem Tetap Berjalan
```

---

## Pengujian 3 — Transient Fault

Tempatkan objek sesaat di depan salah satu sensor.

Hasil yang diharapkan:

```text
Transient Fault Terdeteksi
Output Tetap Stabil
```

---

## Pengujian 4 — Multiple Fault

Matikan dua sensor sekaligus.

Hasil yang diharapkan:

```text
CRITICAL
FAIL-SAFE MODE
HALTED
```

---

# 📈 Mekanisme Fault Tolerance

```text
Pembacaan Sensor
        │
        ▼
 Perhitungan Median
        │
        ▼
 Deteksi Fault
        │
        ▼
 Isolasi Sensor Fault
        │
        ▼
 Majority Voting
        │
        ▼
 Output Final Sistem
```

---

# 📚 Konsep yang Diimplementasikan

* Fault Tolerance
* Dependability
* Reliability Engineering
* Hardware Redundancy
* Triple Modular Redundancy (TMR)
* Majority Voting
* Fault Detection
* Fault Masking
* Graceful Degradation
* Fail-Safe System
* Embedded System
* Internet of Things (IoT)

---

# 👨‍💻 Tim Pengembang

| Nama                    | NIM             |
| ----------------------- | --------------- |
| Faris Arinanta          | 235150300111045 |
| Bakhitah Cinta Syahirah | 235150301111037 |
| Phylicia Ilunary Nyo    | 235150301111012 |
| Adhitya Noer Effendi    | 235150307111024 |

---

# 🎓 Informasi Akademik

Mata Kuliah: **Fault Tolerant System (CCE60309)**

Program Studi Teknik Komputer

Fakultas Ilmu Komputer

Universitas Brawijaya

2026

---

# 📄 Lisensi

Proyek ini dikembangkan untuk keperluan akademik sebagai bagian dari Proyek Akhir Mata Kuliah Fault Tolerant System.
