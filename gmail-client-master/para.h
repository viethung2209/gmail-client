/*
 * File:   para.h
 * Author: rahul
 *
 * Created on 22 February, 2016, 11:52 AM
 */

#ifndef PARA_H
#define PARA_H

#ifdef __cplusplus
extern "C"
{
#endif

//#define FROM "<nghialt4635@gmail.com>"                        // abc@gmail.com
//#define TO "<letrongnghiavanyen@gmail.com>"                  // xyz@gmail.com
//#define MAIL_HEADER_FROM "FromName<nghialt4635@gmail.com>"     // VietHung<abc@gmail.com> -> FromName is  Name's sender 
//#define MAIL_HEADER_TO "ToName<letrongnghiavanyen@gmail.com>"  // TrongNghia<xyz@gmail.com> -> ToName is Name's receiver
//#define UID "nghialt4635@gmail.com"                   // abc@gmail.com 
//#define PWD "20194635" // fwdhasidfnwkejr
    //->Check this link for get it:
    //https://support.google.com/mail/answer/7126229?visit_id=638108198644973122-3360484317&p=BadCredentials&rd=2#cantsignin&zippy=%2Ci-cant-sign-in-to-my-email-client%2Cstep-check-that-imap-is-turned-on%2Cstep-change-smtp-other-settings-in-your-email-client
    //
#define smtp_server_url "smtp.gmail.com" //const
#define domain_name "localhost"          //const

#ifdef __cplusplus
}
#endif

#endif /* PARA_H */
