#include <vector>
#include <cstdint>
#include <cmath>

namespace sd
{
	using std::vector;

	enum Status { OK, ERROR };
	class System
	{
	public:
		struct Input { };
		struct Output { };
		uint32_t n_dim, n_in, n_out;
		virtual Status operator()(Input in, Output out);
	};

	class History/*{{{*/
	{
	public:
		virtual void query(double time, vector<double> input);
		virtual void update(double time, vector<double> output);
	};/*}}}*/

	class RNG/*{{{*/
	{
	public:
		virtual void fill_norm(vector<double> z);
	};/*}}}*/

	class Object
	{
	public:
		virtual uint32_t n_byte() = 0;
		virtual Object& copy() = 0;
	};

	class Scheme : public Object/*{{{*/
	{
	public:
		const uint32_t n_dim, n_in, n_out;
		double dt, time;
		vector<double> state, input, output;
		System &sys;
		History &hist;
		RNG &rng;
		Scheme(double time, double dt, System &sys, History &hist, RNG &rng) :
			n_dim(sys.n_dim), n_in(sys.n_in), n_out(sys.n_out), dt(dt), time(time),
			sys(sys), hist(hist), rng(rng) { }
		System::Input in() { System::Input in; return in; }
		System::Output out() { System::Output out; return out; }
		virtual Status operator()() = 0;
	};/*}}}*/

	class OneStepScheme : public Scheme
	{
	protected:
		vector<double> f, g, z;
		OneStepScheme(double time, double dt, System &sys, History &hist, RNG &rng) :
			Scheme(time, dt, sys, hist, rng), f(n_dim), g(n_dim), z(n_dim) { }
		virtual Status operator()() override
		{
			hist.query(time, input);
			rng.fill_norm(z);
			return sys(in(), out());
		}
       	};

	class IdentityScheme : public OneStepScheme
	{
	public:
		IdentityScheme(double time, System &sys, History &hist, RNG &rng) :
			OneStepScheme(time, 1.0, sys, hist, rng) { }
		Status operator()() override
		{
			OneStepScheme::operator()();
			for (uint32_t i=0; i<state.size(); i++)
				state[i] += f[i] + g[i]*z[i];
			time += dt;
			hist.update(time, output);
			return OK;
		}
	};

	class EulerMaruyamaScheme : public OneStepScheme
	{
		double sqrt_dt;
	public:
		EulerMaruyamaScheme(double time, double dt,
				System &sys, History &hist, RNG &rng) :
			OneStepScheme(time, dt, sys, hist, rng), sqrt_dt(sqrt(dt)) { }
		Status operator()() override
		{
			OneStepScheme::operator()();
			for (uint32_t i=0; i<state.size(); i++)
				state[i] += dt*f[i] + sqrt_dt*g[i]*z[i];
			time += dt;
			hist.update(time, output);
			return OK;
		}
	};

	class EulerMaruyamaColorScheme : public Scheme { };
	class AdditiveHeunScheme : public Scheme { };
}

// vim: foldmethod=marker
