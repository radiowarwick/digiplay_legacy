package org.dps.servicelayer.cartset;

import org.dps.servicelayer.cartset.wrappers.CartsetRequest;
import org.dps.servicelayer.cartset.wrappers.CartsetResponse;
import org.dps.servicelayer.cartset.wrappers.PermissionedCartset;
import org.dps.servicelayer.dto.Cartset;
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
	
	public CartsetResponse getCartset(CartsetRequest params_) {
		CartsetResponse response = new CartsetResponse();
		response.setPermissionedCartset(new PermissionedCartset());
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=?");
			query.setLong(0, params_.getCartsetID());
			
			Cartset cartset = (Cartset) query.uniqueResult();
			System.out.print(cartset.getCartwalls().size());
			response.getPermissionedCartset().setCartset(cartset);
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
	

}
