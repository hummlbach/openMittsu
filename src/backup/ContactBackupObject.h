#ifndef OPENMITTSU_BACKUP_CONTACTBACKUPOBJECT_H_
#define OPENMITTSU_BACKUP_CONTACTBACKUPOBJECT_H_

#include "src/backup/BackupObject.h"
#include "src/backup/SimpleCsvLineSplitter.h"

#include "src/protocol/ContactId.h"
#include "src/crypto/PublicKey.h"
#include "src/protocol/ContactIdVerificationStatus.h"

namespace openmittsu {
	namespace backup {

		class ContactBackupObject : public BackupObject {
		public:
			ContactBackupObject(openmittsu::protocol::ContactId const& id, openmittsu::crypto::PublicKey const& publicKey, openmittsu::protocol::ContactIdVerificationStatus const& verificationStatus, QString const& firstName, QString const& lastName, QString const& nickName, int const& color);
			virtual ~ContactBackupObject();

			openmittsu::protocol::ContactId const& getContactId() const;
			openmittsu::crypto::PublicKey const& getPublicKey() const;
			openmittsu::protocol::ContactIdVerificationStatus const getVerificationStatus() const;
			QString const& getFirstName() const;
			QString const& getLastName() const;
			QString const& getNickName() const;
			int getColor() const;

			static ContactBackupObject fromBackupMatch(QString const& filename, QHash<QString, int> const& headerOffsets, SimpleCsvLineSplitter const& splittedLines);
		private:
			openmittsu::protocol::ContactId m_id;
			openmittsu::crypto::PublicKey m_publicKey;
			openmittsu::protocol::ContactIdVerificationStatus m_verificationStatus;
			QString m_firstName;
			QString m_lastName;
			QString m_nickName;
			int m_color;
		};

	}
}

#endif // OPENMITTSU_BACKUP_CONTACTBACKUPOBJECT_H_
