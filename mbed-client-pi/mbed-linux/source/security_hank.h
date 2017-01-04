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
 
#define MBED_DOMAIN "018ff9a9-8af5-4074-bb63-ee917e956e79"
#define MBED_ENDPOINT_NAME "180733af-3eb8-407c-a431-ca772e36d232"
 
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
"MIIBzzCCAXOgAwIBAgIEV1kOrzAMBggqhkjOPQQDAgUAMDkxCzAJBgNVBAYTAkZ\r\n"
"JMQwwCgYDVQQKDANBUk0xHDAaBgNVBAMME21iZWQtY29ubmVjdG9yLTIwMTYwHh\r\n"
"cNMTYwNzI1MDQ0OTM4WhcNMTYxMjMxMDYwMDAwWjCBoTFSMFAGA1UEAxNJMDE4Z\r\n"
"mY5YTktOGFmNS00MDc0LWJiNjMtZWU5MTdlOTU2ZTc5LzE4MDczM2FmLTNlYjgt\r\n"
"NDA3Yy1hNDMxLWNhNzcyZTM2ZDIzMjEMMAoGA1UECxMDQVJNMRIwEAYDVQQKEwl\r\n"
"tYmVkIHVzZXIxDTALBgNVBAcTBE91bHUxDTALBgNVBAgTBE91bHUxCzAJBgNVBA\r\n"
"YTAkZJMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEqMXXzRXjisvqV1ZqiRocY\r\n"
"VMRYkEuu1urOmdzIpb+UND3rOHas2f4JqyQ9eXd4DTRzZfXy18mIJDMyiZ3i9X8\r\n"
"fzAMBggqhkjOPQQDAgUAA0gAMEUCIEunybg/4Iwc+5qSIO/uHX8nPWPTzZLrsmo\r\n"
"OCb5QyC3cAiEAqv5WcA+X76Cw/PpXSgoTeu21RfenM6kgdbrTPSaP/QQ=\r\n"
"-----END CERTIFICATE-----\r\n";
 
const uint8_t KEY[] = "-----BEGIN PRIVATE KEY-----\r\n"
"MIGHAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBG0wawIBAQQgMcF/tqH9BQGKYR7A\r\n"
"GYEImeTmSMXLHyYvBvwcoewGkFmhRANCAASoxdfNFeOKy+pXVmqJGhxhUxFiQS67\r\n"
"W6s6Z3Milv5Q0Pes4dqzZ/gmrJD15d3gNNHNl9fLXyYgkMzKJneL1fx/\r\n"
"-----END PRIVATE KEY-----\r\n";
 
#endif //__SECURITY_H__
