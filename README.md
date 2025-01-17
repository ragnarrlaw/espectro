# Espectro

Espectro is a command-line audio visualizer that uses Discrete Fourier Transform (DFT) to analyze audio data and visualize it in various patterns using the ncurses library. It supports different visualization modes, including moving waves and wave patterns synchronized with audio playback.

## Features

-   **Audio Reading**: Reads audio data from PCM files.
-   **DFT Calculation**: Computes the Discrete Fourier Transform of the audio data.
-   **Visualization**: Displays the audio spectrum using ncurses.
-   **PortAudio Integration**: Supports real-time audio playback and visualization.

## Prerequisites

-   GCC (GNU Compiler Collection)
-   ncurses library
-   PortAudio library
-   FFmpeg libraries (libavcodec, libavformat, libavutil)

## Setup

1. **Clone the repository**:

    ```sh
    git clone https://github.com/yourusername/espectro.git
    cd espectro
    ```

2. **Install dependencies**:

    - On Debian-based systems:
        ```sh
        sudo apt-get install gcc libncurses5-dev libportaudio2 libavcodec-dev libavformat-dev libavutil-dev
        ```

3. **Build the project**:
    ```sh
    make
    ```

## Usage

1. **Run the visualizer**:

    ```sh
    make run
    ```

2. **Modes**:

    - **Moving Waves**: Defined by the `MOVING_WAVES` macro.
    - **Basic Visualization**: Defined by the `VISUALIZE` macro.
    - **Wave Pattern Audio**: Defined by the `WAVE_PATTERN_AUDIO` macro.

    To switch between modes, modify the `CFLAGS` in the `Makefile`:

    ```makefile
    CFLAGS=-Iinclude -g -DMOVING_WAVES
    ```

## File Structure

-   **include/**: Header files.

    -   `audio.h`: Audio handling and PortAudio callback.
    -   `fft.h`: DFT computation.
    -   `pattern.h`: Visualization functions.
    -   `read.h`: Audio file reading.

    -   `decode.h`: Decode audio files to PCM format.

-   **src/**: Source files.
    -   `audio.c`: PortAudio callback implementation.
    -   `fft.c`: DFT computation implementation.
    -   `main.c`: Main program logic.
    -   `read.c`: Audio file reading implementation.
    -   `deacode.c`: Audio file converting/decoding implementation
-   **Makefile**: Build configuration.
