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
#define MBED_ENDPOINT_NAME "2d7d674e-b4f7-451a-a32b-07fecd4cdc47"
 
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
"MIIBzjCCAXOgAwIBAgIEOudMxDAMBggqhkjOPQQDAgUAMDkxCzAJBgNVBAYTAkZ\r\n"
"JMQwwCgYDVQQKDANBUk0xHDAaBgNVBAMME21iZWQtY29ubmVjdG9yLTIwMTYwHh\r\n"
"cNMTYwNzI4MDkwNjU5WhcNMTYxMjMxMDYwMDAwWjCBoTFSMFAGA1UEAxNJYzE4O\r\n"
"TM4NzgtYjNlMy00ZjRlLThhOGMtYTNiNzhjNTZhNjYxLzJkN2Q2NzRlLWI0Zjct\r\n"
"NDUxYS1hMzJiLTA3ZmVjZDRjZGM0NzEMMAoGA1UECxMDQVJNMRIwEAYDVQQKEwl\r\n"
"tYmVkIHVzZXIxDTALBgNVBAcTBE91bHUxDTALBgNVBAgTBE91bHUxCzAJBgNVBA\r\n"
"YTAkZJMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEg1iPbggkswZvKuSg04HyM\r\n"
"KsfgrLMk0XUXRwxwvhtB+QqeSzaE785HByNTrQA4IVkPdaxuKGeFgbrjacb2mMl\r\n"
"lDAMBggqhkjOPQQDAgUAA0cAMEQCIHk7xKy0lh0gSl2nGkQuJzWQ0M1uFtRXmn6\r\n"
"58OruSRgzAiBlytKcO+aHRs8x0l3p2j7fUkzSLmrwSyaycRofRBtu6Q==\r\n"
"-----END CERTIFICATE-----\r\n";
 
const uint8_t KEY[] = "-----BEGIN PRIVATE KEY-----\r\n"
"MIGHAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBG0wawIBAQQg5k+Jb9iL8t2oejCI\r\n"
"ZO68EPDd9Gy5ioeSsDE2XME6DEqhRANCAASDWI9uCCSzBm8q5KDTgfIwqx+CssyT\r\n"
"RdRdHDHC+G0H5Cp5LNoTvzkcHI1OtADghWQ91rG4oZ4WBuuNpxvaYyWU\r\n"
"-----END PRIVATE KEY-----\r\n";
 
#endif //__SECURITY_H__
