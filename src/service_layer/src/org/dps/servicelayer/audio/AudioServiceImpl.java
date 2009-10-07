package org.dps.servicelayer.audio;

import java.util.LinkedList;
import java.util.List;

import org.dps.servicelayer.AbstractService;
import org.dps.servicelayer.ISearchEngine;
import org.dps.servicelayer.dto.Audio;
import org.hibernate.Query;
import org.hibernate.Session;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.transaction.TransactionDefinition;
import org.springframework.transaction.TransactionStatus;
import org.springframework.transaction.support.DefaultTransactionDefinition;

public class AudioServiceImpl extends AbstractService implements AudioService {

//	private HibernateTemplate hibernateTemplate;
//	
//	public void setHibernateTemplate(HibernateTemplate hibernateTemplate) {
//		this.hibernateTemplate = hibernateTemplate;
//	}
	
	private final static Logger LOGGER = LoggerFactory.getLogger(AudioServiceImpl.class);
	private ISearchEngine searchEngine;
	
	public TestResponse testFunction(TestRequest params_) {
		return new TestResponse();
	}

	@Override
	public AudioSearchResponse search(AudioSearchRequest params_) {
		// TODO Auto-generated method stub
		
		//List audioList = hibernateTemplate.find("from Audio where title=?",params.get_title());
		
		AudioSearchResponse response = new AudioSearchResponse(params_);
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();			
			List<Audio> audios = searchEngine.search(params_.getSearchKeysAsMap(), Audio.class, session);
			List<AudioSummary> audioSummary = new LinkedList<AudioSummary>();
			for (Audio audio : audios) {
				LOGGER.info("Constructing Summary: ", audio.getFileID());
				audioSummary.add(new AudioSummary(audio));
			}
			
			response.setAudios(audioSummary);
			
		} catch (Exception e) {
			ts.setRollbackOnly();
			LOGGER.error("Unable to commit transaction due to exception", e);
			//TODO throw error
		} finally {
			if(ts.isRollbackOnly()) {
				txManager.rollback(ts);
			} else {
				txManager.commit(ts);				
			}
		}
			
		return response;
	}

	@Override
	public GetAudioResponse getAudio(GetAudioRequest params_) {
		GetAudioResponse response = new GetAudioResponse(params_);
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Audio where fileID=?");
			query.setLong(0, params_.getAudioID());
			
			LOGGER.info("Searching for: ", params_.getAudioID());
			
			 Audio track = (Audio) query.uniqueResult();
			 track.makeSafe();
			response.setAudio(track);
		} catch (Exception e) {
			ts.setRollbackOnly();
			LOGGER.error("Unable to commit transaction due to exception", e);
			//TODO throw error
		} finally {
			if(ts.isRollbackOnly()) {
				txManager.rollback(ts);
			} else {
				txManager.commit(ts);				
			}
		}
			
		return response;
	}

	public void setSearchEngine(ISearchEngine searchEngine) {
		this.searchEngine = searchEngine;
	}

}
