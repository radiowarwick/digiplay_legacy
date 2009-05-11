package org.dps.servicelayer.cartset;

import java.util.List;

import org.dps.servicelayer.auth.IFileAuthoriser;
import org.dps.servicelayer.dto.Cartset;
import org.dps.servicelayer.dto.CartsetSummary;
import org.hibernate.Query;
import org.hibernate.Session;
import org.springframework.beans.factory.InitializingBean;
import org.springframework.beans.factory.annotation.Required;
import org.springframework.orm.hibernate3.HibernateTransactionManager;
import org.springframework.transaction.TransactionDefinition;
import org.springframework.transaction.TransactionStatus;
import org.springframework.transaction.support.DefaultTransactionDefinition;

public class CartsetService implements ICartsetService, InitializingBean {

	HibernateTransactionManager txManager;
	IFileAuthoriser authoriser;
	
	public CartsetResponse getCartset(CartsetRequest params_) {
		CartsetResponse response = new CartsetResponse();
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=?");
			query.setLong(0, params_.getCartsetID());
			
			Cartset cartset = (Cartset) query.uniqueResult();
			PermissionedCartset pc = authoriser.getFileAuthorisation(cartset, new PermissionedCartset());
			if(pc.isRead()) {
				response.setPermissionedCartset(pc);
				//This ensures that we don't have any stale collections 
				pc.getItem().makeSafe();
			}
		} catch (Exception e) {
			ts.setRollbackOnly();
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
	
	@SuppressWarnings("unchecked")
	public CartsetsResponse getCartsets(CartsetsRequest params_) {
		CartsetsResponse response = new CartsetsResponse(params_);
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset");
			for(Cartset cartset : (List<Cartset>)query.list()) {
				CartsetSummary summary = new CartsetSummary(cartset);
				PermissionedCartsetSummary permSummary = authoriser.getFileAuthorisation(summary, new PermissionedCartsetSummary());
				if(permSummary.isRead()) {
					response.addPermissionedCartsetSummary(permSummary);
				}
			}
			response.getResultSetDetails().setNumPages(1);
			response.getResultSetDetails().setPageNum(0);
			response.getResultSetDetails().setNumResults(query.list().size());
		} catch (Exception e) {
			ts.setRollbackOnly();
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

	public void afterPropertiesSet() throws Exception {
		
	}

	@Required
	public HibernateTransactionManager getTxManager() {
		return txManager;
	}

	public void setTxManager(HibernateTransactionManager txManager_) {
		txManager = txManager_;
	}

	public IFileAuthoriser getAuthoriser() {
		return authoriser;
	}

	public void setAuthoriser(IFileAuthoriser authoriser_) {
		authoriser = authoriser_;
	}
	

}
