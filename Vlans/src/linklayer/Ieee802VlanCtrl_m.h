//
// Generated file, do not edit! Created by opp_msgc 4.1 from linklayer/Ieee802VlanCtrl.msg.
//

#ifndef _IEEE802VLANCTRL_M_H_
#define _IEEE802VLANCTRL_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0401
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include "MACAddress.h"
#include "Ieee802Ctrl_m.h"
// }}



/**
 * Class generated from <tt>linklayer/Ieee802VlanCtrl.msg</tt> by opp_msgc.
 * <pre>
 * class Ieee802VlanCtrl extends Ieee802Ctrl
 * {
 *     string ifName;		 
 * }
 * </pre>
 */
class Ieee802VlanCtrl : public ::Ieee802Ctrl
{
  protected:
    opp_string ifName_var;

    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee802VlanCtrl&);

  public:
    Ieee802VlanCtrl();
    Ieee802VlanCtrl(const Ieee802VlanCtrl& other);
    virtual ~Ieee802VlanCtrl();
    Ieee802VlanCtrl& operator=(const Ieee802VlanCtrl& other);
    virtual Ieee802VlanCtrl *dup() const {return new Ieee802VlanCtrl(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual const char * getIfName() const;
    virtual void setIfName(const char * ifName_var);
};

inline void doPacking(cCommBuffer *b, Ieee802VlanCtrl& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Ieee802VlanCtrl& obj) {obj.parsimUnpack(b);}


#endif // _IEEE802VLANCTRL_M_H_
