# Raspberry Pi Setup Guide

This guide prepares a fresh Raspberry Pi OS image so the `pi-grid` program can run.

## 1. Prepare the SD card
1. Flash the latest Raspberry Pi OS Lite to an SD card.
2. Boot the Pi and log in via HDMI or SSH.
3. Update packages and enable SSH if needed:
   ```bash
   sudo apt update && sudo apt upgrade -y
   sudo raspi-config nonint do_ssh 0
   ```
4. Install required packages:
   ```bash
   sudo apt install -y libmonome-dev libasound2-dev pkg-config
   ```
5. Disable HDMI output to save power (optional):
   ```bash
   sudo /usr/bin/tvservice -o
   ```

## 2. Verify PiSound MIDI ports
1. Ensure the PiSound HAT is connected and powered.
2. Reboot the Pi.
3. List ALSA clients and look for `pisound`:
   ```bash
   aconnect -l
   ```
   You should see an entry similar to:
   ```
   client 20: 'pisound' [type=kernel]
   ```
4. If the client appears, the PiSound MIDI ports are ready to use.

Your Raspberry Pi is now configured to run the `pi-grid` application.
