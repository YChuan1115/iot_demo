/*
 * Copyright (c) 2015 ARM Limited. All rights reserved.
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
#define MBED_ENDPOINT_NAME "41f0a38b-5fc8-42af-b4c8-0b3628d09a8a"
 
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
"MIIBzzCCAXOgAwIBAgIEKGilgjAMBggqhkjOPQQDAgUAMDkxCzAJBgNVBAYTAkZ\r\n"
"JMQwwCgYDVQQKDANBUk0xHDAaBgNVBAMME21iZWQtY29ubmVjdG9yLTIwMTYwHh\r\n"
"cNMTYwODEwMDE1MjI3WhcNMTYxMjMxMDYwMDAwWjCBoTFSMFAGA1UEAxNJYzE4O\r\n"
"TM4NzgtYjNlMy00ZjRlLThhOGMtYTNiNzhjNTZhNjYxLzQxZjBhMzhiLTVmYzgt\r\n"
"NDJhZi1iNGM4LTBiMzYyOGQwOWE4YTEMMAoGA1UECxMDQVJNMRIwEAYDVQQKEwl\r\n"
"tYmVkIHVzZXIxDTALBgNVBAcTBE91bHUxDTALBgNVBAgTBE91bHUxCzAJBgNVBA\r\n"
"YTAkZJMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEEO5jFi3wFicGzbg6y6bOi\r\n"
"FObAiCc+n5dFFje8uYL6AGuzm10fZ74+Wtx9W40uo3SH9rpTuJC+SNzsW4WKmVQ\r\n"
"fjAMBggqhkjOPQQDAgUAA0gAMEUCIBVMg/NbmxGC8KBAzpY7aHSHK09hDixfqo2\r\n"
"6HscTAplEAiEAuelQWKIgNHKpaocEup8xJVsr//3pJ28KQmWhtJvq/f8=\r\n"
"-----END CERTIFICATE-----\r\n";
 
const uint8_t KEY[] = "-----BEGIN PRIVATE KEY-----\r\n"
"MIGHAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBG0wawIBAQQgz0tM2hi2wLjojBOl\r\n"
"cP9AQSo+cJCBAAwcbbrDsAD3QvOhRANCAAQQ7mMWLfAWJwbNuDrLps6IU5sCIJz6\r\n"
"fl0UWN7y5gvoAa7ObXR9nvj5a3H1bjS6jdIf2ulO4kL5I3OxbhYqZVB+\r\n"
"-----END PRIVATE KEY-----\r\n";
 
#endif //__SECURITY_H__
