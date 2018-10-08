#include "src/utility/ThreadContainer.h"

#include "src/exceptions/InternalErrorException.h"
#include "src/utility/Logging.h"
#include "src/utility/MakeUnique.h"
#include "src/utility/QObjectConnectionMacro.h"

namespace openmittsu {
	namespace utility {

		template <typename T>
		ThreadContainer<T>::ThreadContainer() : QObject() {
			m_threadWorker = std::make_unique<T>();
			m_threadWorker->moveToThread(&m_workerThread);
			m_workerThread.start();
		}

		template <typename T>
		ThreadContainer<T>::~ThreadContainer() {
			//
		}

		template <typename T>
		QObject* ThreadContainer<T>::getQObjectPtr() const {
			return m_threadWorker.get();
		}

		template <typename T>
		T& ThreadContainer<T>::getWorker() {
			return *m_threadWorker;
		}

		template <typename T>
		T const& ThreadContainer<T>::getWorker() const {
			return *m_threadWorker;
		}

		template class ThreadContainer<openmittsu::database::DatabaseThreadWorker>;
		template class ThreadContainer<openmittsu::dataproviders::MessageCenterThreadWorker>;
	}
}
