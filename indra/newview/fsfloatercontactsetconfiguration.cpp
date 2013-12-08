/*
 * @file fsfloatercontactsetconfiguration.cpp
 * @brief Contact set configuration floater
 *
 * (C) 2013 Cinder Roxley @ Second Life <cinder.roxley@phoenixviewer.com>
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "llviewerprecompiledheaders.h"
#include "fsfloatercontactsetconfiguration.h"
#include "lggcontactsets.h"

FSFloaterContactSetConfiguration::FSFloaterContactSetConfiguration(const LLSD& target_set)
:	LLFloater(target_set)
{
	mContactSet = target_set.asString();
}

BOOL FSFloaterContactSetConfiguration::postBuild()
{
	LLStringUtil::format_map_t map;
	map["NAME"] = mContactSet;
	setTitle(getString("title", map));

	mSetSwatch = getChild<LLColorSwatchCtrl>("set_swatch");
	if (mSetSwatch)
	{
		mSetSwatch->setCommitCallback(boost::bind(&FSFloaterContactSetConfiguration::onCommitSetColor, this));
	}
	
	mGlobalSwatch = getChild<LLColorSwatchCtrl>("global_swatch");
	if (mGlobalSwatch)
	{
		mGlobalSwatch->setCommitCallback(boost::bind(&FSFloaterContactSetConfiguration::onCommitDefaultColor, this));
	}
	
	mNotificationCheckBox = getChild<LLCheckBoxCtrl>("show_set_notifications");
	if (mNotificationCheckBox)
	{
		mNotificationCheckBox->setCommitCallback(boost::bind(&FSFloaterContactSetConfiguration::onCommitSetNotifications, this));
	}
	return TRUE;
}

void FSFloaterContactSetConfiguration::onOpen(const LLSD& target_set)
{
	mSetSwatch->set(LGGContactSets::getInstance()->getSetColor(mContactSet), TRUE);
	mGlobalSwatch->set(LGGContactSets::getInstance()->getDefaultColor(), TRUE);
	mNotificationCheckBox->set(LGGContactSets::getInstance()->getNotifyForSet(mContactSet));
}

void FSFloaterContactSetConfiguration::onCommitSetColor()
{
	LGGContactSets::getInstance()->setSetColor(mContactSet, mSetSwatch->get());
}

void FSFloaterContactSetConfiguration::onCommitSetNotifications()
{
	LGGContactSets::getInstance()->setNotifyForSet(mContactSet, mNotificationCheckBox->getValue().asBoolean());
}

void FSFloaterContactSetConfiguration::onCommitDefaultColor()
{
	LGGContactSets::getInstance()->setDefaultColor(mGlobalSwatch->get());
}
