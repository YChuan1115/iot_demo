/*copyright (c) 2015 ARM Limited. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef __SECURITY_H__
#define __SECURITY_H__
 
#include <inttypes.h>
 
#define MBED_DOMAIN "c1893878-b3e3-4f4e-8a8c-a3b78c56a661"
#define MBED_ENDPOINT_NAME "da3c152f-5e48-4f89-8eb6-e9fae4b32a14"
 
const uint8_t SERVER_CERT[] = "-----BEGIN CERTIFICATE-----\r\n"
"MIIBmDCCAT6gAwIBAgIEVUCA0jAKBggqhkjOPQQDAjBLMQswCQYDVQQGEwJGSTEN\r\n"
"MAsGA1UEBwwET3VsdTEMMAoGA1UECgwDQVJNMQwwCgYDVQQLDANJb1QxETAPBgNV\r\n"
"BAMMCEFSTSBtYmVkMB4XDTE1MDQyOTA2NTc0OFoXDTE4MDQyOTA2NTc0OFowSzEL\r\n"
"MAkGA1UEBhMCRkkxDTALBgNVBAcMBE91bHUxDDAKBgNVBAoMA0FSTTEMMAoGA1UE\r\n"
"CwwDSW9UMREwDwYDVQQDDAhBUk0gbWJlZDBZMBMGByqGSM49AgEGCCqGSM49AwEH\r\n"
"A0IABLuAyLSk0mA3awgFR5mw2RHth47tRUO44q/RdzFZnLsAsd18Esxd5LCpcT9w\r\n"
"0tvNfBv4xJxGw0wcYrPDDb8/rjujEDAOMAwGA1UdEwQFMAMBAf8wCgYIKoZIzj0E\r\n"
"AwIDSAAwRQIhAPAonEAkwixlJiyYRQQWpXtkMZax+VlEiS201BG0PpAzAiBh2RsD\r\n"
"NxLKWwf4O7D6JasGBYf9+ZLwl0iaRjTjytO+Kw==\r\n"
"-----END CERTIFICATE-----\r\n";
 
const uint8_t CERT[] = "-----BEGIN CERTIFICATE-----\r\n"
"MIIB0DCCAXOgAwIBAgIEKrIz8jAMBggqhkjOPQQDAgUAMDkxCzAJBgNVBAYTAkZ\r\n"
"JMQwwCgYDVQQKDANBUk0xHDAaBgNVBAMME21iZWQtY29ubmVjdG9yLTIwMTgwHh\r\n"
"cNMTcwMTAzMDYyNjI0WhcNMTgxMjMxMDYwMDAwWjCBoTFSMFAGA1UEAxNJYzE4O\r\n"
"TM4NzgtYjNlMy00ZjRlLThhOGMtYTNiNzhjNTZhNjYxL2RhM2MxNTJmLTVlNDgt\r\n"
"NGY4OS04ZWI2LWU5ZmFlNGIzMmExNDEMMAoGA1UECxMDQVJNMRIwEAYDVQQKEwl\r\n"
"tYmVkIHVzZXIxDTALBgNVBAcTBE91bHUxDTALBgNVBAgTBE91bHUxCzAJBgNVBA\r\n"
"YTAkZJMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAE087iw/oBGWywINuxKqHV1\r\n"
"9nudEgK9ehdpn1XkxXO2PhFrZQMU6wBB5L92sUYgembrIrw+LqumegiJQtcc6bY\r\n"
"iTAMBggqhkjOPQQDAgUAA0kAMEYCIQC+YW0SUZQLdRgRNeo5+0v0Rw7BXVYVOCo\r\n"
"FZIT7EqyzSQIhANRXh0/K1pBSq4j4vbYgw0Sol85pc4ElvJQRTlpC/3+a\r\n"
"-----END CERTIFICATE-----\r\n";
 
const uint8_t KEY[] = "-----BEGIN PRIVATE KEY-----\r\n"
"MIGHAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBG0wawIBAQQgnQgyZOxM0OljewEW\r\n"
"nY/WzkYhS/z3gifNmO9q4Hy1nlWhRANCAATTzuLD+gEZbLAg27EqodXX2e50SAr1\r\n"
"6F2mfVeTFc7Y+EWtlAxTrAEHkv3axRiB6ZusivD4uq6Z6CIlC1xzptiJ\r\n"
"-----END PRIVATE KEY-----\r\n";
 
#endif //__SECURITY_H__
