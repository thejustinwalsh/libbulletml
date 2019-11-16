/// BulletML を実行する
/// Run BulletML
/**
 * 使い方：
 * Usage:
 *
 * BulletMLRunner を継承していくつかの純粋仮想関数を実装する。
 * Inherit from BulletMLRunner and implement some pure virtual functions.
 */

#ifndef BULLETRUNNER_H_
#define BULLETRUNNER_H_

#include "bulletmlcommon.h"
#include "bulletmltree.h"

#include <cstdlib>
#include <vector>

class BulletMLParser;
class BulletMLNode;
class BulletMLRunnerImpl;

typedef std::vector<double> BulletMLParameter;

/// BulletMLRunner が状態伝達に使用するクラス
/// Class used by BulletMLRunner for state propagation
class BULLETML_API BulletMLState {
public:
    BulletMLState(BulletMLParser *bulletml, const std::vector<BulletMLNode *> &node, std::shared_ptr<BulletMLParameter> param) :
		m_bulletml(bulletml),
		m_node(node.begin(), node.end()),
		m_parameter(param) {
	}

    BulletMLParser *getBulletML() { return m_bulletml; }
    const std::vector<BulletMLNode *> &getNode() const { return m_node; }
    std::shared_ptr<BulletMLParameter> getParameter() { return m_parameter; }

private:
    BulletMLParser *m_bulletml;
    std::vector<BulletMLNode *> m_node;
    std::shared_ptr<BulletMLParameter> m_parameter;
};

/// BulletML を実行するクラス
/// Class to execute BulletML
/**
 * <pre>
 * 使い方。
 * Usage.
 *  1. これを継承して、Bullet を実際に動かせるクラスを作る。
 *     Inherit from this, create a class that can move the Bullet.
 *  2. 純粋仮想関数を全て実装する。
 *     Implement all pure virtual functions.
 *  3. 必要なら、changeDirection などのために必要な仮想関数を実装する。
 *     If necessary, implement the necessary virtual functions for changeDirection, etc.
 *  4. このクラスのオブジェクトに対して、com_->run(); などとする。
 *     For objects of this class, call com_->run();
 * </pre>
 */

class BULLETML_API BulletMLRunner {
public:
    explicit BulletMLRunner(BulletMLParser *bulletml);
    explicit BulletMLRunner(BulletMLState *state);
    virtual ~BulletMLRunner();

    /// 実行する
	/// Execute
    void run();

public:
    /// 実行が終了しているかどうか
	/// Whether execution has ended
    bool isEnd() const;

public:
    // ----- 絶対実装しなければならない関数群の始まり -----
	// ----- Start of functions that must absolutely be implemented -----
	///
    //@{
    /// この弾の角度を求める
	/// Find the angle of the bullet
    /**
     * @return 角度を度単位で、上方向 0 で時計周りで返す
	 *         Return angle in degrees, clockwise in upward direction 0
     */
    virtual double getBulletDirection() = 0;
    /// この弾から自機を狙う角度を求める
	/// Find the angle that aims at your ship from this bullet
    /**
     * @return 角度を度単位で、上方向 0 で時計周りで返す
     */
    virtual double getAimDirection() = 0;
    /// この弾の速度を求める
	/// Find the speed of this bullet
    virtual double getBulletSpeed() = 0;
    /// デフォルトの速度を求める
	/// Find the default speed
    virtual double getDefaultSpeed() = 0;
    /// ランクを求める
	/// Ask for a rank
    /**
     * @return 0 から 1 までの実数
	 *         Real number from 0 to 1
     */
    virtual double getRank() = 0;
    /// action を持たない弾を作る
	/// Make bullets without an action
    virtual void createSimpleBullet(double direction, double speed) = 0;
    /// action を持つ弾を作る
	/// Make a bullet with an action
    /**
     * @param state
     * 新しい弾の BulletMLRunner のコンストラクタに渡すこと。
     * もし渡さないのであれば、delete で解放しなければならない。
	 * Passing it to the new bullet BulletMLRunner's constructor.
	 * If you do not pass it you have to release it with delete.
	 */
    virtual void createBullet(BulletMLState *state, double direction, double speed) = 0;
    /// 弾の基準となるターンの値を返す、通常はフレーム数
	/// It returns the value of the turn which becomes the reference of the
	/// bullet, usually the number of frames
    /**
     * @return
     * ゲームごとの基準でオーダーは変更して構いませんが、
     * 負数は許されません。
     * xml データ上で、wait と term のオーダーが揃っていれば問題ありません。
	 * You can change the order according to the standard of each game,
	 * but negative numbers are not allowed.
     * There is no problem as long as the order of wait and term is on
	 * the xml data.
     */
    virtual int getTurn() = 0;
    /// 死ぬ
	/// Die
    virtual void doVanish() = 0;
    //@}
    // ----- 絶対実装しなければならない関数群の終わり -----
	// ----- End of functions that must absolutely be implemented -----

    // ----- 必要があれば実装する関数群の始まり -----
	// ----- Start of functions to be implemented if necessary -----
    //@{
    /// 弾の方向を指定した方向に変更する
	/// Change direction of bullet to specified direction
    virtual void doChangeDirection(double) {}
    /// 弾の速度を指定した値に変更する
	/// Change the speed of the bullet to the specified value
    virtual void doChangeSpeed(double) {}
    /// accel に対するインターフェイス
	/// Interface to accel
    /**
     * @todo
     * horizontal, vertical の type は未実装です。
     * どれも absolute になってしまいます。
	 * The horizontal and vertical types are not implemented yet.
     * It will become absolute as well.
     */
    virtual void doAccelX(double) {}
    /// accel に対するインターフェイス
	/// Interface to accel
    /**
     * @todo
     * horizontal, vertical の type は未実装です。
     * どれも absolute になってしまいます。
	 * The horizontal and vertical types are not implemented yet.
	 * It will become absolute as well.
	 */
    virtual void doAccelY(double) {}
    /// 弾の速さの X 方向成分を返します
	/// Returns the X direction component of the bullet speed
    /**
     * accel を使う場合はオーバーライドして下さい
	 * Override when using accel
     */
    virtual double getBulletSpeedX() { return 0; }
    /// 弾の速さの Y 方向成分を返します'
	/// Returns the Y direction component of bullet speed
    /**
     * accel を使う場合はオーバーライドして下さい
	 * Override when using accel
     */
    virtual double getBulletSpeedY() { return 0; }
    //@}
    // ----- 必要があれば実装する関数群の終わり -----
	// ----- End of functions to be implemented if necessary -----

    /// 乱数を返す
	/// Returns a random number
    /**
     * 見てのとおり、デフォルトでは std::rand が用いられます。
	 * As you can see, std::rand is used by default.
     */
    virtual double getRand() { return (double)rand() / RAND_MAX; }

private:
    /// BulletMLRunnerImpl をオーバーライドする場合、これもオーバーライドする
	/// If you override BulletMLRunnerImpl, also override this
    virtual BulletMLRunnerImpl *makeImpl(BulletMLState *state);

protected:
    std::vector<BulletMLRunnerImpl *> m_impl;
};

#endif // ! BULLETRUNNER_H_
